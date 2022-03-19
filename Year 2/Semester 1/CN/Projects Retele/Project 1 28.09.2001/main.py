# import socket
# from time import sleep
# s=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
# i=0
# while True :
#
#
#     s.sendto(str.encode(str(i)),("172.30.113.250",7777))
#     i+=1
#     sleep(1)


# import socket
# s=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
# s.sendto(b"hey bietch",("192.168.0.212",7777))
# print(s.recv(10))

import socket
s=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
s.bind(("0.0.0.0",5555))
buff,addr=s.recvfrom(100)
print(buff)
s.sendto(b"hello", addr)