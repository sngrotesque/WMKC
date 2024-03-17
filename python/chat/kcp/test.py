from typing import Union, Tuple
import threading
import struct
import socket
import zlib
import time

class myKCP:
    def __init__(self, laddr :str, lport :int, family :int = socket.AF_INET):
        self.laddr = laddr
        self.lport = lport

        self.fd = socket.socket(family, socket.SOCK_DGRAM, socket.IPRPOTO_UDP)
        self.fd.bind((self.laddr, self.lport))

        self.clients = []

    def __recv(self, length :int):
        data = b''
        while length:
            tmp, = self.fd.recvfrom(min(length, 4096))
            data += tmp
            length -= len(tmp)
        return data

    def send(self, seq :int, data :bytes, addr :Tuple[str, int]):
        packet_seq = struct.pack('!I', seq)
        packet_len = struct.pack('!I', len(data))
        packet_dat = data
        packet_crc = struct.pack('!I', zlib.crc32(data))
        
        packet_all = packet_seq + packet_len + packet_dat + packet_crc
        
        self.fd.sendto(packet_all, addr)

    def recv(self):
        packet_seq, addr = struct.pack('!I', self.fd.recvfrom(4))
        packet_len, addr = struct.pack('!I', self.fd.recvfrom(4))
        packet_dat, addr = self.__recv(packet_len)
        packet_crc, addr = struct.pack('!I', self.fd.recvfrom(4))
        
        if zlib.crc32(packet_dat) != packet_crc:
            raise RuntimeError('crc no.')
        
        return packet_seq, addr, packet_dat

# 使用SimpleKCP的服务器端
def server():
    kcp_server = myKCP('localhost', 37789)
    while True:
        data, addr = kcp_server.recv()
        print(f"Received from {addr}: {data}")
        kcp_server.send(b"ACK", addr)

# 使用SimpleKCP的客户端
def client(server_ip, server_port):
    kcp_client = myKCP('localhost', 0)
    while True:
        kcp_client.send(b"Hello KCP", (server_ip, server_port))
        data, _ = kcp_client.recv()
        print(f"Received: {data}")
        time.sleep(1)  # 简单的发送间隔

# 启动服务器和客户端线程
server_thread = threading.Thread(target=server)
client_thread = threading.Thread(target=client, args=('localhost', 37789))

server_thread.start()
client_thread.start()



