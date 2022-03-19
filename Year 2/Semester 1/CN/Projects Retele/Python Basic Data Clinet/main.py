
import socket, pickle
import struct

try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect(("192.168.0.155", 1234))

    # string
    #message = input("Give message to send: ")

    #s.send(message.encode())

    # integer

    #integer = int(input("Give integer to send: "))

    #s.send(struct.pack('!i', integer))

    # array of integers

    arr = [1, 2, 3, 4, 5, 6, 7, 8]

    data_string = pickle.dumps(arr)

    s.send(data_string)

    nr = s.recv(1024)
    sum = struct.unpack("!i", nr)[0]

    print("The sum of all the elements is: ", str(sum), "\n")

    s.close()
except socket.error as msg:
    print("Error " + str(msg))
    exit(-1)

