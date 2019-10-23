from socket import *
serverPort = 12000
serverName = '192.168.56.1'
serverSocket = socket(AF_INET, SOCK_DGRAM)
serverSocket.bind((serverName, serverPort))
serverSocket.listen(1)
print("The server is ready to receive")
while True:
    connectionSocket, addr = serverSocket.accept()
    sentence = connectionSocket.recv(1024)
    sentence = sentence.decode()
    connectionSocket.send(sentence.encode())
    connectionSocket.close()
