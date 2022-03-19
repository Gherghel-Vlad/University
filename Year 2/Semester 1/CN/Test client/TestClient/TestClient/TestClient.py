
import select
import socket
import struct
import threading
import struct
import sys
import random
import time
import pickle

IP = '192.168.0.155'
PORT = 1234
SERV_ADDR = (IP, PORT)

nr_of_digits =-1
guessed = True
lock = threading.Lock()
def udp_listen():
    str, addr = us.recvfrom(1024)
    lock.acquire()
    guessed = False
    print(str.decode())
    lock.release()


if __name__ == '__main__':
    ts = None
    us = None
    try:
        ts = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        ts.connect(SERV_ADDR)
        ts.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        # tcp_socket.setblocking(False)
        us = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        us.bind(ts.getsockname())
        # udp_socket.setblocking(False)
    except socket.error as msg:
        print("Error: ", msg.strerror)
        exit(-1)
    t = threading.Thread(target = udp_listen)
    t.start()

    nr_of_digits = struct.unpack('!i',ts.recv(4))[0]

    print("Number of digits: ", nr_of_digits)

    while(guessed):
        try:

            lock.acquire()
            random_number = random.randint(0,9)
            if(guessed):
                print(random_number)

            ts.send(struct.pack('!i', random_number))

            places = pickle.loads(ts.recv(100))
            if(guessed):
                print(places)

            lock.release()

            time.sleep(int(sys.argv[1]))
        except EOFError:
            break
        except BrokenPipeError:
            break



    

