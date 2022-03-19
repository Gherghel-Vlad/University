

import socket
import os
s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.connect(("192.168.0.155",1234))
s.send(b"Hello")

if os.startfile():
    while(1):
        print(s.recv(1024))
        exit(0)

while(1):
    s.send(input())
s.close()
