#!/usr/bin/env python
import socket

TCP_IP = '150.162.209.13'
TCP_PORT = 6414
BUFFER_SIZE = 512  # Normally 1024, but we want fast response

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((TCP_IP, TCP_PORT))
s.listen(1)
s.settimeout(10)

conn, addr = s.accept()
print 'Connection address:', addr
while 1:
    data = conn.recv(BUFFER_SIZE)
    if not data: 
    	print "No data received"
    if data:    	
    	print "received data:", data
    conn.send(data)  # echo
conn.close()