import socket
import time
import struct

from ftClientListener import ftClientListener

################################################################################
##
## ftClientConnection class
##
## CS 372 - Project 2 - Jeremy Prater
##

class ftClientConnection:
    def __init__(self, serverHost, serverPort, clientPort, command, file):
        # Initalize local variables from input
        self.serverHost = serverHost
        self.serverPort = serverPort
        self.clientPort = clientPort
        self.command = command
        self.file = file

        # Setup listner socket (for incoming file data)
        self.listener = ftClientListener(self.clientPort, self.command, self.file)
        self.listener.start()

    def __enter__(self):
        # Entry point
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        # Object is being destroyed, close connection
        print("Closing connection to ftserver {}:{}".format(self.serverHost, self.serverPort))
        self.listener.listening = False
        self.ftSock.close()

    def ftConnect(self):
        # Connect to the server
        print("Connecting to ftserver {}:{}".format(self.serverHost, self.serverPort))
        self.ftSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            self.ftSock.connect((self.serverHost, self.serverPort))
        except:
            print("Connecting to ftserver {}:{} failed!".format(self.serverHost, self.serverPort))
            return False
        return True

    def ftSendCommand(self):
        # Send the command to the server
        payload = bytearray()
        hostname = socket.gethostname()
        payload.extend(struct.pack("!HHHB", self.clientPort, len(self.file), len(hostname), self.command))
        payload.extend(hostname.encode('ASCII'))
        if len(self.file) > 0:
            payload.extend(self.file.encode('ASCII'))
        self.ftSock.send(payload)