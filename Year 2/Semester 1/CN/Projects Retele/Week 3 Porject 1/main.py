import socket
s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.bind(("0.0.0.0",7777))
s.listen(5)
cs,addr=s.accept()
print("Sent by " + str(addr))
b=cs.recv(10)
print(b.decode())
a=str(b.decode())
a=a[::-1]
cs.send(a.encode())
cs.close()