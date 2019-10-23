from socket import *

clientSocket = socket(AF_INET, SOCK_DGRAM)
serverName = "10.124.6.90"
serverPort = 13000
fileName = input("Enter the file name ").encode()
clientSocket.sendto(fileName, (serverName, serverPort))
fileContent, serverAddr = clientSocket.recvfrom(1024)
print(fileContent.decode())
clientSocket.close()
