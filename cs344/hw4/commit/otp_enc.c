/***
Arthur Liou
CS344

This program connects to otp_enc_d, and asks it to perform a one-time pad style encryption as detailed above. By itself, otp_enc doesn’t do the encryption - otp_end_d does. The syntax of otp_enc is as follows:

otp_enc plaintext key port
***/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>
#include <netinet/in.h>

void error(const char *msg) { perror(msg); exit(1); } // Error function used for reporting issues

int main(int argc, char *argv[]) {
	int socketFD, portNumber, charsWritten, charsRead;
	struct sockaddr_in serverAddress;
	struct hostent* serverHostInfo;
	char buffer[100000];

	if (argc < 4) { fprintf(stderr, "USAGE: %s plaintext key port\n", argv[0]); exit(1); } // Check usage & args

	// Set up the server address struct
	memset((char*)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	portNumber = atoi(argv[3]); // Get the port number, convert to an int from a string
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverHostInfo = gethostbyname("localhost"); // Convert the machine name into a special form of address
	if (serverHostInfo == NULL) { fprintf(stderr, "CLIENT: ERROR, no such host\n"); exit(1); }
	memcpy((char*)&serverAddress.sin_addr.s_addr, (char*)serverHostInfo->h_addr, serverHostInfo->h_length); // Copy in the address
	
	// Set up the socket (TCP socket)
	socketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (socketFD < 0) error("CLIENT: ERROR opening socket");

	// Connect to server
	if (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {// Connect socket to addy
		error("CLIENT: ERROR connecting");
	}

	// Start Implementation for OTP
	// Getting plaintext and keys to send
	char* plaintext = argv[1]; //Grab Plaintext
	char* key = argv[2]; //Grab key
	char wholePackage[250000]; 
	// Create a data package for both plaintext, key, status of encryption, end of both plaintext and key
	
	// Edge Case Checking
	// Plaintext, Key length, invalid characters
	// Opening key
	if (open(key, O_RDONLY) < 0) {
		printf("Client Key - Could not open \n");
		exit(1);
	}
	// Opening plaintext
	if (open(plaintext, O_RDONLY) < 0) {
		fprintf(stderr, "Plaintext File - Couldn't Open\n");
		exit(1);
	} 
	memset(buffer, '\0', sizeof(buffer)); // Clear out the buffer array
	read(open(plaintext, O_RDONLY), buffer, sizeof(buffer) - 1);

	// Checking for invalid characters in plaintext, which is all in buffer
	int i;
	for (i = 0; i < strlen(buffer); i++) {
		if (buffer[i] > 90 || (buffer[i] > 32 && buffer[i] < 65)) {
			fprintf(stderr, "Client Encryption Error - Invalid characters in: %s\n", plaintext);
			exit(1);
		}
	}

	//Add Encrypted Flag to wholePackage, add plaintext (in buffer) to wholepackage, remove the last line of the package, and add # as a flag to signal the end of plaintext. Also Grabbing Length of Plaintext 
	//Templated from "Get Input Message from User" from client.c
	strcpy(wholePackage, "e");
	strcat(wholePackage, buffer);
	int wholePackageLength = strlen(wholePackage);
	wholePackage[wholePackageLength - 1] = '\0';
	strcat(wholePackage, "1");

	/***
	* Adding Key to Package
	* Also Checking for Edge Cases
	***/

	//Grab and Read key. Save Length
	memset(buffer, '\0', sizeof(buffer)); // Clear out the buffer array
	read(open(key, O_RDONLY), buffer, sizeof(buffer));
	int keyLength = strlen(buffer);

	//Compare Length of entiredata package vs key length. If key is too long, end
	if (wholePackageLength > keyLength) {
		printf("Client Enc Error - key \'%s\' is too short\n", key);
		exit(1);
	}

	// Checking for invalid characters in key. Copied from Above
	for (i = 0; i < keyLength; i++) {
		if (buffer[i] > 90 ||( buffer[i] > 32 && buffer[i] < 65)) {
			printf("Error - Invalid character(s) in %s\n", plaintext);
			exit(1);
		}
	}
	
	//Templated from "Get Input Message from User" from client.c
	strcat(wholePackage, buffer);
	wholePackage[strlen(wholePackage) - 1] = '\0';
	strcat(wholePackage, "2");
	//wholePackage is Now Complete
	
	// Template from Client.C
	// Send message to server
	charsWritten = send(socketFD, wholePackage, strlen(wholePackage), 0); // Write to the server
	if (charsWritten < 0) error("CLIENT: ERROR writing to socket");
	if (charsWritten < strlen(wholePackage)) printf("CLIENT: WARNING: Not all data written to socket!\n");

	// Get return message from server
	memset(buffer, '\0', sizeof(buffer)); // Clear out the buffer again for reuse
	charsRead = recv(socketFD, buffer, sizeof(buffer) - 1, 0); // Read data from teh socket, leaving \0 at end
	if (charsRead < 0) error("CLIENT: ERROR reading from socket");
	//If we receive a failure message from the server/daemon/socket
	if (strstr(buffer, "failed") != NULL) {
		printf("Fail Error: otp_enc cannot use otp_dec_d server.\n");
		exit(1);
	}
	
	printf("%s\n", buffer);
	// Close socket
	close(socketFD); 
	return 0;
}
