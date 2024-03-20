import socket

fd = socket.socket()
fd.connect(('127.0.0.1', 48291))
try:
    while True:
        fd.send(b'\x00\x00\x00\x01\x00\x00\x00\x02SNA+p\xff')
        print(fd.recv(32))
except:
    fd.close()
