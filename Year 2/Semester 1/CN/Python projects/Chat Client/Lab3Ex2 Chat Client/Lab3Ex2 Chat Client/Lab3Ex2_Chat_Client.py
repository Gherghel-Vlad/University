


import socket
import pickle, threading

PORT = 7000
def list_updating():
    global clients_list, s
    while(True):
        message = s.recv(1024).decode()
        list_mess = str(message).split(';')
        print(str(message))
        if(list_mess[0] == 'disconnect'):
            clients_list.remove((list_mess[1], int(list_mess[2])))
        else:
            clients_list.append((list_mess[1], int(list_mess[2])))

        print(clients_list)

def listen_udp():
    global u
    while(True):
        buff, addr = u.recvfrom(1024)
        print(str(addr) + " sent: " + str(buff))

try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect(("192.168.0.155", PORT))

    u = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    u.bind(("0.0.0.0", PORT))

    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    
except socket.error as msg:
    print(msg.strerror)
    exit(-1)

clients_list = pickle.loads(s.recv(1024))

print(clients_list)

t = threading.Thread(target=list_updating, daemon=True)
t.start()
t1 = threading.Thread(target=listen_udp, daemon=True)
t1.start()


while(True):
    a = input()
    if(a == "QUIT"):
        s.send(a.encode())
        s.close()
        u.close()
        exit(0)
    else:
        for c in clients_list:
            u.sendto(a.encode(), (c[0], PORT))

s.close()







