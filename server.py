__author__ = 'nidzo'

import socket

HOST = ''  # Symbolic name meaning all available interfaces

# SOCKET 1
PORT1 = 50007
socket1 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socket1.bind((HOST, PORT1))
socket1.listen(1)

# SOCKET 2
PORT2 = 53007
socket2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socket2.bind((HOST, PORT2))
socket2.listen(1)

conn, addr = socket1.accept()
conn2, addr2 = socket2.accept()

while True:
    data = conn.recv(1024)  # Receive from socket 1
    if not data:
        break
    print 'Received from 1st socket: ', repr(data)
    print 'Sending to 2nd socket: ', repr(data)
    conn2.sendall(data)  # Send to socket 2

conn.close()
conn2.close()
