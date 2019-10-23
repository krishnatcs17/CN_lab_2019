from socket import *
serverPort = 13000
serverName = '10.124.6.90'
serverSocket = socket(AF_INET, SOCK_DGRAM)
serverSocket.bind((serverName, serverPort))
print("The server is ready to receive ..")
while True:
    fileName, addr = serverSocket.recvfrom(1024)
    fileName = fileName.decode()
    print("File name - " + fileName)
    f = open(fileName, 'r')
    serverSocket.sendto(f.read().encode(), addr)
    f.close()
