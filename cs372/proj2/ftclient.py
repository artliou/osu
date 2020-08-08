#Programmer Name: Arthur Liou
#Program Name: Project 2 - File Transfer
#Program Description: FT Client. This is the client side of a file transfer application
#Course Name: CS372 
#Last Modified: Thursday, 11/22/18

# Usage Syntax: python3 ftclient.py [serverHost] [portNumber] [commandFlag] [data-portNumber] [transferfileName - optional]

# !/usr/bin/python
# import libraries and sockets API
import socket, select, sys
import fileinput
import threading
from os import path

# Client Initiate Contact Function
# Rubric: Verification - ftclient setup
def initiateContact():
	# Check for Correct Number of Arguments
	# Verification - ftclient setup
	if len(sys.argv) < 5:
		print("Insufficient command line arguments.")
		print(
			"Usage Syntax: python3 ftclient.py [serverHost] [portNumber] [commandFlag] [data-portNumber] [transferfileName - optional]")
		sys.exit(1)

	# Extra Credit: Authentication - Username/Password
	# Username and password prompt
	username = input("Username: ")
	password = input("Password: ")
	authentication = username + " " + password

	# Parsing sys.argv / command line arguments
	# sys.argv[0] is just this.fileName
	serverHost = sys.argv[1];
	serverPort = int(sys.argv[2])
	commandFlag = sys.argv[3]
	message = commandFlag + " " + serverHost
	# dataPort = int(sys.argv[4])
	dataPort = serverPort + 1
	# Check Command Flag is Valid
	if commandFlag != "-g" and commandFlag != "-l":
			print("Invalid Command Flag Given.")
			print("FT Program: Exiting")
			sys.exit(0)

	# print("Creating Sockets")
	# Pseudo Coding: Create two separate sockets to the server & separate threads to send specific commands. This will allow for multi-threading and easier readability / functionality to where each 

	# Socket - Sends Commands to Server
	serverSendSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	serverSendSocket.connect((serverHost, serverPort))

	# Socket - Receives Data from Server
	serverReceiveSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	serverReceiveSocket.bind(('', dataPort))
	serverReceiveSocket.listen(5)

	# print("Sockets Creation Complete")

	# Extra Credit: Authentication - Username/Password
	serverSendSocket.send(authentication.encode("utf-8"))

	serverAuthResponse = serverSendSocket.recv(bufferSize)
	serverAuthResponseClean = serverAuthResponse.decode("utf-8")
	# print(serverAuthResponseClean)
	if serverAuthResponseClean == "Invalid username or password.":
		print(serverAuthResponseClean)
		sys.exit(0)
	# End Auth

	# Grabs Current Host's Socket Name & Appends to Message
	# This allows one to go from flip1 to flip2 etc
	# Resource: https://www.geeksforgeeks.org/display-hostname-ip-address-python/
	currentHost = socket.gethostname()
	message = commandFlag + " " + currentHost
	# print("Python", socket.gethostname())

	# Review System Arguments
	# print("Sys.args:", sys.argv, len(sys.argv))
	# Checks for Command Flag & Number of Arguments
	if len(sys.argv) == 6:
		fileName = sys.argv[5] # File name will always be last argument
		message = message + " " + fileName
		# Must have "-g" flag
		# print("Flag", command)
		if commandFlag != "-g":
				print("Incorrect Command Flag. Must be -g.")
				print("FT Program: Exiting")
				sys.exit(0)
		# Checking for file overwrite
		if path.exists(fileName):
			userRes = input("File already exists. Do you want to overwrite? (yes/no)\n")
			if userRes == "no" or userRes == "No":
				print("Not overwriting")
				print("FT Program: Exiting")
				sys.exit(0)
# 			elif (userRes != "yes" and userRes != "no"):
#         print("Invalid Arguments: please use yes/no (lowercase)")
#         print("FT Program: Exiting")
#         sys.exit(0)
			print("'No' or 'no' not selected. Overwriting.")

	# Requirements: Make Request Function
	# Send Message to Server
	# Verification (Control) - command sent
	def makeRequest():
		serverSendSocket.send(message.encode("utf-8"))
		# print("Message Sent:", message, type(message))
	
	# Send Message
	makeRequest()

	# Resource: https://www.tutorialspoint.com/python/python_multithreading.htm
	# Split each thread into separate functions: one for receivingFile, one for receivingDirectory, one for serverComms
	# Verification (Data) - Connection
	if len(sys.argv) == 6:
		receiveFileThread = threading.Thread(target=receiveFile, args=(serverReceiveSocket, fileName), )
		receiveFileThread.start()
	else:
		receiveDirectoryThread = threading.Thread(target=receiveDirectory, args=(serverReceiveSocket, ), )
		receiveDirectoryThread.start()
	# Verification (Control) - Connection
	serverCommunication = threading.Thread(
		target=serverComms, args=(serverSendSocket, ), )
	serverCommunication.start()

# End Initiate Contact Function

# Function Definitions for each separate Thread, also any Global Variables
bufferSize = 5000
# Two functions to receive data: one for file, or for directory
# This function is used just to recieve a file from the server.
# Verification (Data) - File Save
def receiveFile(serverReceiveSocket, fileName):
	receiveBuffer, hostPort = serverReceiveSocket.accept()
	print("Receiving File:", fileName)
	# Create and Open File in write mode
	outFile = open(fileName,"w+")

	while True:
		fileData = receiveBuffer.recv(bufferSize)
		# print("Client Receiving FileData Line:", fileData)
		if not fileData or len(fileData) == 0: break
		outFile.write(fileData.decode("utf-8"))
	# Done Writing to File & Close it
	outFile.close()
	# Verification (Data) - Transfer Complete
	print("File transfer complete.")

# Function to specifically receive directory from Server & print to console.
# Verification (Data) - Directory Listing
def receiveDirectory(serverReceiveSocket):
	receiveBuffer, hostPort = serverReceiveSocket.accept()
	# print(receiveBuffer, address)
	rawStructure = receiveBuffer.recv(bufferSize)
	print("Receiving directory structure")
	# Could've left as is, but used this to clean up the console printout
	directoryStructure = rawStructure.split()
	# print("Listings: ", dirListing)
	for file in directoryStructure:
		print(file.decode("utf-8"))

# Maintaining a socket open for server communciation
def serverComms(serverSocket):
	# print("Client: Server Comms Ready")
	while True:
		rawServerResponse = serverSocket.recv(bufferSize)
		# print("Raw Server Response:", rawServerResponse)
		if not rawServerResponse or len(rawServerResponse) == 0: break
		# Tough, but found out the /quit comes back as "b'/quit\x00'"
		if rawServerResponse == b'/quit\x00': break
		serverResponse = rawServerResponse.decode("utf-8")
		print(serverResponse)
		if serverResponse == "File not found.": break
	# Verification (Control) - Connection Closed
	serverSocket.close()

# Run Function
initiateContact()
