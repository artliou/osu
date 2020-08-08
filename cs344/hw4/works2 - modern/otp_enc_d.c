#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg) { perror(msg); exit(1); } // Error function used for reporting issues

int main(int argc, char *argv[]) {
	int listenSocketFD, establishedConnectionFD, portNumber, charsRead;
	socklen_t sizeOfClientInfo;
	char buffer[255];
	struct sockaddr_in serverAddress, clientAddress;
	pid_t spawnpid = -5;
	int childExitMethod = -5;
	int childPID[256]; // Supports up to 256 child processes
	int childCount = 0;

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
	
	while(1) {
		// Deal with zombie processes (there will always be one zombie after first run)
		if (childCount) { // If there are any zombie processes in childPID array
			int complete = waitpid(childPID[childCount], &childExitMethod, WNOHANG);
			if (complete) { // If the top element PID process has finished, pop it
				childCount--;
			}
		}

		// Accept a connection, blocking if one is not available until one connects
		sizeOfClientInfo = sizeof(clientAddress); // get teh size of the address for the client that will connect
		establishedConnectionFD = accept(listenSocketFD, (struct sockaddr *)&clientAddress, &sizeOfClientInfo); // Accept previously created socketFD
		if (establishedConnectionFD < 0) error("ERROR on accept");
		//printf("SERVER: Connected Client at port %d\n", ntohs(clientAddress.sin_port));
		spawnpid = fork();
		switch(spawnpid) {
			case -1:
				perror("Hull Breach!");
				exit(1);
				break;
			case 0: {// Child process
				char plaintext[131072];
				char key[131072];
				char encryptedtext[131072];
				memset(plaintext, '\0', sizeof(plaintext));
				memset(key, '\0', sizeof(key));
				memset(encryptedtext, '\0', sizeof(encryptedtext));
				recv(establishedConnectionFD, buffer, 1, 0); // Getting the indicating character (ie: 'e' or 'd')
				if (buffer[0] != 'e') { // If otp_enc isn't used, print error and exit with 1
					// Send an unsucccess message back to the client
					charsRead = send(establishedConnectionFD, "bad", 3, 0); // Send success back
					if (charsRead < 0) error("ERROR writing to socket");
					close(establishedConnectionFD); // Close the exiting socket which is connected to the client
					exit(1); // Exiting child process
				}

				// Get the message from the client
				memset(buffer, '\0', 256);
				while (strstr(buffer, "@") == NULL) { // Looping for plaintext
					charsRead = recv(establishedConnectionFD, buffer, 1, 0); // Read the client's message from the socket
					if (charsRead < 0) error("ERROR reading from socket");
					strcat(plaintext, buffer); // Storing the sent plaintext in plaintext
				}
				plaintext[strlen(plaintext)-1] = '\0'; // Getting rid of '@' marker
				while (strstr(buffer, "$") == NULL) { // Looping for key
					charsRead = recv(establishedConnectionFD, buffer, 1, 0); // Read the client's message from the socket
					if (charsRead < 0) error("ERROR reading from socket");
					strcat(key, buffer); // Storing the sent key in key
				}
				key[strlen(key)-1] = '\0'; // Getting rid of '$' marker

				//printf("SERVER: Received plaintext: \"%s\"\n", plaintext);
				//printf("SERVER: Received key: \"%s\"\n", key);

				// Encrypting plaintext using the key
				int i;
				char temp;
				for (i = 0; i < strlen(plaintext); i++) {
					if (plaintext[i] == 32) plaintext[i] = 64; // Converting all ' ' to '@'
					if (key[i] == 32) key[i] = 64; // Converting all ' ' to '@'
					temp = plaintext[i] + (key[i] - 64);
					if (temp > 90) temp = (temp - 64) % 27 + 64;
					encryptedtext[i] = temp;
					//encryptedtext[i] = (plaintext[i] + key[i]) % 27 + 64;
					if (encryptedtext[i] == 64) encryptedtext[i] = 32; // Converting '@' back to ' '
					//printf("Encrypted char: %c\n", encryptedtext[i]);
				}
				//strcat(encryptedtext, "$"); // Adding a terminator
				//printf("\"%s\"\n", encryptedtext);

				// Send a Success message back to the client
				charsRead = send(establishedConnectionFD, encryptedtext, strlen(encryptedtext), 0); // Send success back
				if (charsRead < 0 || charsRead != strlen(encryptedtext)) error("ERROR writing to socket");
				close(establishedConnectionFD); // Close the exiting socket which is connected to the client
				exit(0); // Exiting child process
				break;
			}
			default: {// Parent process
				int complete = waitpid(spawnpid, &childExitMethod, WNOHANG); // Non-blocking, but keeps child process in check
				if (!complete) { // If child process is incomplete, store its PID in array called childPID[] to deal with later
					childPID[childCount++] = spawnpid;
				}
				break;
			}
		}
		
	}


	close(listenSocketFD); // Close the listening socket
	return 0;
}