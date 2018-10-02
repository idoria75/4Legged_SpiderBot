import socket
import sys
import time

HOST = "127.0.0.1"   # Symbolic name meaning all available interfaces
PORT = 6412 # Arbitrary non-privileged port

a = 0

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.settimeout(3)

while(1):

    s.sendto(str(a) ,(HOST,PORT))
    
    try:    
        data, addr = s.recvfrom(1024)
        print(data)
        if(data == "ACK"):
            a = a+1
        if(data == "END"):
            break

    except socket.timeout:
        print("No data received")    

    time.sleep(1)

s.close()