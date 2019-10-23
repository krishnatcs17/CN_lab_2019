from socket import *
serverPort = 12000
serverName = '10.124.6.94'
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName, serverPort))
fileName = input("Enter file name: ")
print("Establishing connection ...")
print("File contents:")
clientSocket.send(fileName.encode())
fileContents = clientSocket.recv(1024).decode()
print('\n', str(fileContents), '\n')
clientSocket.close()

