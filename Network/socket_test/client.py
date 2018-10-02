#!/usr/bin/python2.7
import time
import socket

HOST = "150.162.209.65"
PORT = 6412
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

sock.bind((HOST, PORT))
sock.settimeout(.5)

a = 0
i = 0

while(1):

    try:
        data, addr = sock.recvfrom(1024)
        print(data)
        sock.sendto("ACK", addr)
    
    except socket.timeout:
        print("No data received")
    
    i = i+1
    print("It = ", i)

    time.sleep(1)
    
sock.close()