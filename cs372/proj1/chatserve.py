# Arthur Liou
# CS372
# Chat Client - C. This is the server side of a chat application
#!/usr/bin/python

# import libraries and sockets API
import socket, select, sys
from thread import *

# 1) Start-up function & "Main"
##### Section 1 #####
def startup():
	# Edge Case for Correct Number of Arguments on the Cmd Line
	if len(sys.argv) != 2:
			print("Error: Invalid arguments.\n")
			exit()

	portNumber = int(sys.argv[1])  # reads in port number from stdin
	# Creating Socket
	# Resource: https://docs.python.org/2/howto/sockets.html
	# Resource: https://docs.python.org/2/library/socket.html
	# Create an INET, STREAMing socket
	serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	#bind the socket to a public host,
	# and a well-known port
	serverSocket.bind(('', portNumber))
	# Become a server socket
	serverSocket.listen(3)

	print "Chat Server has started"
	# Create Main Loop of the server
	# Loops forever and accepts incoming socket requests from clients until socket is closed.
	while 1:
		openSocket, address = serverSocket.accept()
		# Resource: https://docs.python.org/3/library/_thread.html
		# Resource: https://www.tutorialspoint.com/python3/python_multithreading.htm
		# Resource: https: // www.geeksforgeeks.org/socket-programming-multi-threading-python/
		# Extra Credit attempt for Multi-Threaded Server. Created Two Threads - one for receiving messages and one for sending
		# 2nd Parameter for start_new_thread requires a tuple, but since receiveMessage and sendMessage doesn't have any arguemnts, passing as empty
		# sendMessage(openSocket)
		# receiveMessage(openSocket)
		start_new_thread(receiveMessage, (openSocket, ))
		start_new_thread(sendMessage, (openSocket, ))
	serverSocket.close()

# 2) Send Message
# After starting a new thread, this function will loop & continue to send messages to the client until the chat ends
def sendMessage(openSocket):
	print "Server - Ready to Send Messages to New Client"
	while True:
		# Resource: https://docs.python.org/2/library/functions.html#raw_input
		# Grabs input from stdin
		serverMessage = raw_input()
		# Ends loop & program if input is "/quit". Also if /quit is received, it will send that to the openSocket, which will bounce to the receiveMessage thread and then close the socket.
		if serverMessage == "/quit":
			openSocket.send("/quit\0")
			break
		# Send Message from Server to Socket
		# hardcoded Host A handle / username as Server
		openSocket.send("Server>" + serverMessage + "\0")
	print "Server - Send Message Ended"
	# openSocket.close() I Found that I'd get a "socket error [Errno 9] Bad file descriptor HTTP server" if I left this uncommented. This is because in receiveMessage the openSotkcet.recv is still open. So that means I can only quit in "one direction"
# End sendMessage function

# 3) Receive Message
# After starting a new thread, this function will loop & continue to receive messages to the client until the chat ends
def receiveMessage(openSocket):
	print "Server - Ready to Receive Messages from New Client"
	while True:
		# Socket is expecteding Max of 512: I choose 512 since it is a power of 2, includes 500-char message, 10-char username, 1 char >, 1 char space (or w/e the extra char could be)
		clientMessage = openSocket.recv(512)
		# Ends loop & program if input is "/quit"
		if clientMessage == "/quit":
			print "Server - Chat Closed"
			break
		# Prints Message from Client
		print clientMessage
	print "Server - Closing Socket Connection"
	openSocket.close()
	exit()
# End receivingMessage function

# Start Chat Server / Python Script
startup()
