#!/usr/bin/env python
import socket

TCP_IP = '150.162.209.13'
TCP_PORT = 6412
BUFFER_SIZE = 1024
MESSAGE = "Hello, World!"

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((TCP_IP, TCP_PORT))
data = s.recv(BUFFER_SIZE)
s.send(MESSAGE)
s.close()

print "received data:", data