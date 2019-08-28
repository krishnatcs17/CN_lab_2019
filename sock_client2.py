from socket import *
serverPort = 12000
serverName = '192.168.56.1'
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((serverName, serverPort))
sentence = input("Enter file name: ")
clientSocket.send(sentence.encode())
modifiedSentence = clientSocket.recv(1024).decode()
file = open(modifiedSentence, 'r')
for each in file: 
    print (each)