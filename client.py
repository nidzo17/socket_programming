__author__ = 'nidzo'

import socket

HOST = ''  # localhost

# SOCKET 1
PORT1 = 50007
socket1 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socket1.connect((HOST, PORT1))

# SOCKET 2
PORT2 = 53007
socket2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
socket2.connect((HOST, PORT2))

send_data = raw_input('> ')  # Send to socket 1
print 'Sending to 1st socket: ', repr(send_data)
socket1.sendall(send_data)
while True:
    recv_data = socket2.recv(1024)  # Receive from socket 2
    if not recv_data:
        break
    print 'Received from 2nd socket: ', repr(recv_data)

socket1.close()
socket2.close()
