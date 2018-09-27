import socket

TCP_IP = '127.0.0.1'
TCP_PORT = 5005
BUFFER_SIZE = 20  # Normally 1024, but we want fast response

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.bind((TCP_IP, TCP_PORT))
s.listen(0)

conn, addr = s.accept()
print 'Connection address:', addr

while 1:
    data = conn.recv(BUFFER_SIZE)
    if data == "10" : break
    print "received data: ", data
    print "type: ", type(data)
    conn.send(data)  # echo
conn.close()