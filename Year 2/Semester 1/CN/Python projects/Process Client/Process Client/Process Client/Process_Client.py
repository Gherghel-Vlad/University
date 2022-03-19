
import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.connect(("192.168.0.155", 1234))

a = s.recv(1024)

print(a.decode())

