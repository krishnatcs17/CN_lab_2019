from socket import *

serverSocket = socket(AF_INET, SOCK_STREAM)
serverPort = 12000
serverName = "10.124.6.94"
serverSocket.bind((serverName, serverPort))
serverSocket.listen(1)
print("Starting the server")
while True:
    conn, addr = serverSocket.accept()
    fileName = conn.recv(1024)
    with open(fileName.decode(), "r") as f:
        reply = f.read()
    conn.send(reply.encode())
    conn.close()
