#! /bin/python2
#####################################################################################
##
## CS 372 Project 1
##
## Chat server
##
## Jeremy Prater
##

from socket import *
import argparse
import sys

#####################################################################################
##
## Get the port number from the command line
##

def GetCommandArguments():
    parser = argparse.ArgumentParser(description='Start the chatserve server')
    parser.add_argument('port', metavar='port', type=int,
                    help='port number to listen for connections on')

    args = parser.parse_args()
    return args.port


#####################################################################################
##
## Main server loop
##

def ServerChatLoop(serverSocket, serverHandle):
    serverSocket.listen(1)
    print "Server listening on port {0}".format(serverPort)
    connectionSocket, addr = serverSocket.accept()
    handle = connectionSocket.recv(1024);
    print "User : [" + handle + "] connected!"
    running = True
    while running:
        serverData = connectionSocket.recv(1024);
        if not serverData or serverData == '\\quit':
            print "User : [" + handle + "] disconnected!"
            running = False
        else:
            print handle + "> " + serverData
            # Get input data and send
            sys.stdout.write(serverHandle + ' ')
            sys.stdout.flush()
            inputData = sys.stdin.readline().rstrip()
            connectionSocket.send(serverHandle + ' ' + inputData);



#####################################################################################
##
## Program entry point
##

serverHandle = 'server>'
serverPort = GetCommandArguments()
serverSocket = socket(AF_INET, SOCK_STREAM)
serverSocket.bind(('', serverPort))


while 1:
    ServerChatLoop(serverSocket, serverHandle)