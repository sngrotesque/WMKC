import threading
import socket

def create_default_socket(addr :str, port :int):
    fd = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
    fd.bind((addr, port))
    return fd

def loop(fd :socket.socket):
    heart = fd.recv(8)
