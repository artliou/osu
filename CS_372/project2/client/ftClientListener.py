import socket
import threading
import subprocess
import struct
import os

################################################################################
##
## ftClientListener class
##
## CS 372 - Project 2 - Jeremy Prater
##

class ftClientListener(threading.Thread):
    def __init__(self, clientPort, command, file):
        # Setup local variables from input
        threading.Thread.__init__(self);
        self.clientPort = clientPort
        self.command = command
        self.file = file

    def GetData (self):
        # Get data from socket until it is empty or closed.
        payload = bytearray();
        while True:
            data = self.ftConnection.recv(1024);
            if not data:
                return payload
            payload.extend(data)

    def run(self):
        # Startup the socket to listen for server response.
        print("ftclient listener thread on port {}".format(self.clientPort))
        self.ftSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.ftSocket.bind ((socket.gethostname(), self.clientPort))
        self.ftSocket.settimeout(1)
        self.ftSocket.listen(1)
        self.listening = True
        self.timeoutCounter = 0;
        print ('Waiting for accept on {}'.format(self.clientPort))

        #  Client listener loop
        while self.listening:
            try:
                # Wait for new connection
                self.ftConnection, self.ftAddress = self.ftSocket.accept()
                print ('New data connection from {}'.format(self.ftAddress))
                data = self.GetData();
                # Send response payload length...
                if self.command == 0:
                    # list command
                    print ("{}".format(data.decode('ASCII')))
                elif self.command == 1:
                    # get file command
                    if os.path.isfile(self.file):
                        print ("File {} exists in local directory Not overwriting!".format(self.file))
                    else:
                        if len(data) > 0:
                            outFile = open(self.file, 'wb')
                            outFile.write(data)
                            outFile.close()
                            print ("Wrote {} bytes to file {}".format(len(data), self.file))
                        else:
                            print ("File {} not found on server.".format(self.file))

                else:
                    self.ftConnection.send(0);
                self.listening = False

            # Socket time out to re-run listener loop and check for exit signal
            except socket.timeout as t:
                self.timeoutCounter += 1
                if self.timeoutCounter < 5:
                    pass
                else:
                    raise socket.timeout

        # Shutdown client listener
        self.ftSocket.close()
        print("ftclient closing port {}".format(self.clientPort))