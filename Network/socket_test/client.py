#!/usr/bin/python2.7

import time
import socket
import sys

HOST = ""
PORT = 6412
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

sock.bind((HOST, PORT))
sock.settimeout(3)

a = 0

while(1):
    try:
        data, addr = sock.recvfrom(1024)
        print(data)
        sock.sendto("ACK", addr)
    
    except socket.timeout:
        print("No data received")
    # time.sleep(.5)
    
sock.close()
