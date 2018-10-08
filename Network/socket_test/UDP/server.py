#!/usr/bin/python2.7
import socket
import time

HOST = "150.162.209.13"
PORT = 6412

CLIENT = "150.162.209.106"
CPORT = 6413

a = 0

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.settimeout(3)
# Needs to bind to listen from ESP
s.bind((HOST, PORT))

# s2 = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
# s2.settimeout(3)
# # Needs to bind to listen from ESP
# s2.bind((CLIENT, CPORT))


while(1):

    a = a+1
    s.sendto(str(a) ,(HOST, CPORT))
    try:    
        data, addr = s.recvfrom(128)
        print("Data received: " + data)
        # if(data == "ACK"):
        #     a = a+1
        # if(data == "END"):
        #     break
    except socket.timeout:
        print("No data received")    

    time.sleep(1)

s.close()