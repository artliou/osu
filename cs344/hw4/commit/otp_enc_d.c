/***
Arthur Liou
CS344
***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

// Templated from Server.c
void error(const char *msg) { perror(msg); exit(1); } // Error function used for reporting issues

int main(int argc, char *argv[]) {
	int listenSocketFD, establishedConnectionFD, portNumber, charsRead;
	socklen_t sizeOfClientInfo;
	char buffer[255];
	struct sockaddr_in serverAddress, clientAddress;

	if (argc < 2) { fprintf(stderr,"USAGE: %s port\n", argv[0]); exit(1); } // Check usage & args

	// Set up the address struct for this process (the server)
	memset((char *)&serverAddress, '\0', sizeof(serverAddress)); // Clear out the address struct
	portNumber = atoi(argv[1]); // Get the port number, convert to an integer from a string
	serverAddress.sin_family = AF_INET; // Create a network-capable socket
	serverAddress.sin_port = htons(portNumber); // Store the port number
	serverAddress.sin_addr.s_addr = INADDR_ANY; // Any address is allowed for connection to this process

	// Set up the socket
	listenSocketFD = socket(AF_INET, SOCK_STREAM, 0); // Create the socket
	if (listenSocketFD < 0) error("ERROR opening socket");

	// Enable the socket to begin listening
	if (bind(listenSocketFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) // Connect socket to port
		error("ERROR on binding");
	listen(listenSocketFD, 5); // Flip the socket on - it can now receive up to 5 connections
	
	//Start of OTP Implementation / End of first part of server.c template
	//Variables to Prep and Set the Key, Plaintext, and Chiper
	char plaintext[100000];
	char ciphertext[100000];
	char key[100000];
	memset(plaintext, '\0', sizeof(plaintext));
	memset(ciphertext, '\0', sizeof(ciphertext));
	memset(key, '\0', sizeof(key));

	while(1) {
		// Template from Server.c
		// Accept a connection, blocking if one is not available until one connects
		sizeOfClientInfo = sizeof(clientAddress); // get teh size of the address for the client that will connect
		establishedConnectionFD = accept(listenSocketFD, (struct sockaddr *)&clientAddress, &sizeOfClientInfo); // Accept previously created socketFD
		if (establishedConnectionFD < 0) error("ERROR on accept");

		//Start Implementation Again / Start Child Processes
		pid_t pid = fork();
		switch(pid) {
			case -1:
				error("Fork Err");
				exit(1);
				break;
			case 0: {
				//Start By Getting the indicating character of e or d
				recv(establishedConnectionFD, buffer, 1, 0);
				if (buffer[0] != 'e') {
					// Sends a failutre message back to client
					charsRead = send(establishedConnectionFD, "failed", 6, 0);
					if (charsRead < 0) error("ERROR writing to socket");
					close(establishedConnectionFD);
					exit(1);
				}

				// Get the message from the client
				memset(buffer, '\0', 256);
				while (strstr(buffer, "1") == NULL) {
					//Read Message from Socket
					charsRead = recv(establishedConnectionFD, buffer, 1, 0);
					if (charsRead < 0) error("ERROR reading from socket");
					//Add message to plaintext
					strcat(plaintext, buffer);
				}

				plaintext[strlen(plaintext) - 1] = '\0';

				// Waiting for Key
				while (strstr(buffer, "2") == NULL) {
					charsRead = recv(establishedConnectionFD, buffer, 1, 0); 
					//Read Message from Socket
					if (charsRead < 0) error("ERROR reading from socket");
					strcat(key, buffer);
				}
				
				key[strlen(key) - 1] = '\0';

				// Encrypting plaintext using the key
				// The various if statements are to catch spaces, @, $ and to make sure that the new encrypted character is inserter into cipher
				int i;
				for (i = 0; i < strlen(plaintext); i++) {
					if (plaintext[i] == 32) {
						plaintext[i] = 64;
					}
					if (key[i] == 32) {
						key[i] = 64;
					}
					//Start Encryption Process with the key
					char tempChar = plaintext[i] + (key[i] - 64);

					if (tempChar > 90) {
						tempChar = (tempChar - 64) % 27 + 64;
					}
					//Move Encrypted Character to ciphertext
					ciphertext[i] = tempChar;

					if (ciphertext[i] == 64) {
						ciphertext[i] = 32;
					}
				}

				// Send message back to the client, close socket, and break out of the switch statement and while loop
				charsRead = send(establishedConnectionFD, ciphertext, strlen(ciphertext), 0); // Send success back
				if (charsRead < 0 || charsRead != strlen(ciphertext)) error("ERROR writing to socket");
				close(establishedConnectionFD);
				exit(0);
				break;
			}
			default: {
				break;
			}
		}
	}
	// Close the listening socket
	close(listenSocketFD); 
	return 0;
}