// Arthur Liou
// CS372
// Chat Client - C. This is the client side of a chat application

// Resources: http://beej.us/guide/bgnet/html/single/bgnet.html
// Resource: My CS344 Socket project, the server side file/code
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <fcntl.h>
#include <assert.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#define bufferLength 1000000

int serverPort;
void* handleRequest(void*);

/***
* Server Main / Startup
* Verification - ftserve setup
* Verification (Control) - Connection
***/
int main(int argc, char* argv[]) {
	// Validate command line arguments
	if (argc != 2) {
		printf("Incorrect command line arguments\n");
		printf("Usage Syntax: ftserver [port]\n");
		return 1;
	}
	serverPort = atoi(argv[1]);
	struct sockaddr_in server;

	// Start Server Socket Setup. From CS344
	int listenSocketFD = socket(AF_INET, SOCK_STREAM, 0);
	// Connection Verifiaction
	if (listenSocketFD < 0) {
		printf("Error opening socket.\n");
		return 1;
	}
	
	memset(&server, '\0', sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(serverPort);
	// Error Handling
	if (bind(listenSocketFD, (struct sockaddr *)&server , sizeof(server)) != 0) 
	{
		perror("Server Socket Binding failed.");
		return 1;
	}
	listen(listenSocketFD, 5);
	printf("Server now open and waiting on on %d.\n", serverPort);
	// End Server Socket Setup / Running Successfully

	// Setting Up on-going connectionSocket with client
	int clientSocket;
	struct sockaddr_in client;
	socklen_t clientSize = sizeof(client);
	// Verification - Server Continues
	// Server is kept open and can accept additional connections until terminaled by supeviser
	while (1) {
		clientSocket = accept(listenSocketFD, (struct sockaddr *)&client, &clientSize);
		pthread_t threadID;
		if (pthread_create(&threadID, NULL, handleRequest, (void*)&clientSocket) < 0) {
			perror("Failed to Create Thread.");
			return 1;
		}
	}
	close(listenSocketFD);
	printf("Server closed on %d.\n", serverPort);
	return 0;
}

/***
* HandleRequest
* Verification (Control) - accept/interpret command
***/
void* handleRequest(void* socketID) {
	int clientSocket = *(int *) socketID;
	int dataPort = serverPort + 1;
	char command[bufferLength], message[bufferLength], authentication[bufferLength], authResponse[bufferLength];

	printf("Processing an Incoming Request.\n");
	// int messageSize;
	int messageSize = recv(clientSocket, authentication, bufferLength, 0);
	printf("Incoming Auth: %s\n", authentication);
	if (messageSize == 0) {
		printf("Connection closed by Client - Auth.\n");
		return; // Breaks out of handleRequest while keeping server Open
	} else if (messageSize < 0) {
		perror("Failure: Didn't receive message.");
		return; // Breaks out of handleRequest while keeping server Open
	}

	/***
	* Extra Credit: Authentication
	***/
	char *username, *password;
	username = strtok(authentication, " ");
	password = strtok(NULL, " ");
	printf("Client's Username / Pass: %s, %s\n", username, password);

	if (strcmp(username, "admin") != 0 || strcmp(password, "pw") != 0) {
		sprintf(authResponse, "Invalid username or password.");
		printf("Server Authentication Failed: %s\n", authResponse);
		write(clientSocket, authResponse, strlen(authResponse));
		return; // Breaks out of handleRequest while keeping server Open
	} else {
		printf("Server: received connection from client.\n");
		write(clientSocket, "Connected", strlen("Connected"));
	}
	// End Authentication

	/***
	* Process Client Command
	***/
	messageSize = recv(clientSocket, command, bufferLength, 0);
	if (messageSize == 0) {
		printf("Connection closed by Client.\n");
		return; // Breaks out of handleRequest while keeping server Open
	} else if (messageSize < 0) {
		perror("Failure: Didn't receive message.");
		return; // Breaks out of handleRequest while keeping server Open
	}
	// Grabs Command Flag & serverHost
	char* commandFlag = strtok(command, " \0\n");
	char* requestedHost = strtok(NULL, " \0\n");
	// printf("Requested Host: %s\n", requestedHost);
	// printf("Command: %s\n", command);

	// List Directory Request
	// Verification (Data) - Directory Listing
	if (strcmp(commandFlag, "-l") == 0) {
		printf("Request for list directory\n");
		char responseDirectory[bufferLength];
		// Data Socket Prep. From CS344
		struct sockaddr_in serverAddr;
		struct hostent *serverHost;
		
		memset(&serverAddr, '0', sizeof(serverAddr));
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons(dataPort);
		
		serverHost = gethostbyname(requestedHost);
		memcpy((char*)&serverAddr.sin_addr.s_addr, (char*)serverHost->h_addr, serverHost->h_length);
		//Socket Creation
		int connectionSocket = socket(AF_INET, SOCK_STREAM, 0);
		if (connectionSocket < 0)
		{
			printf("Socket failed.\n");
			connectionSocket = 1;
			return;
		}
		if (connect(connectionSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) != 0)
		{
			printf("Connection failed.\n");
			connectionSocket = 1;
			return;
		}
		// End Data Socket Setup

		// Grabing directory
		// Resources: https://stackoverflow.com/questions/3554120/open-directory-using-c
		// Resources: https://www.sanfoundry.com/c-program-list-files-directory/
		DIR *dir;
		struct dirent *current;
		dir = opendir(".");
		if (dir) {
			while((current = readdir(dir)) != 0) {
				strcat(responseDirectory, current->d_name);
				strcat(responseDirectory, " "); // Separate each file on a new line
			}
			write(connectionSocket, responseDirectory, strlen(responseDirectory));
		} else {
			perror("Server Error: Directory open failed");
			exit(1);
		}
		closedir(dir);
		close(connectionSocket);
		printf("Sending directory contents.\n");
	}
	// File Transfer Request
	// Verification (Data) - File Transfer
	else if (strcmp(commandFlag, "-g") == 0) {
		char* fileName = strtok(NULL, " \0\n");
		printf("File Requested: %s\n", fileName);
		// File Not Found Section
		// If unable to access / ie not found, then send message back to client saying the file isn't found
		if (access(fileName, F_OK) == -1) {
			sprintf(message, "%s", "File not found.");
			printf("%s Sending error message to client.\n", message);
			write(clientSocket, message, strlen(message));
			return; // Breaks out of handleRequest while keeping server Open
		} else {
			struct sockaddr_in serverAddr;
			struct hostent *serverHost;
			
			memset(&serverAddr, '0', sizeof(serverAddr));
			serverAddr.sin_family = AF_INET;
			serverAddr.sin_port = htons(dataPort);
			
			serverHost = gethostbyname(requestedHost);
			// printf(serverHost);
			// printf(requestedHost);
			memcpy((char*)&serverAddr.sin_addr.s_addr, (char*)serverHost->h_addr, serverHost->h_length);
			
			int connectionSocket = socket(AF_INET, SOCK_STREAM, 0);

			if (connectionSocket < 0) {
				printf("Socket failed.\n");
				connectionSocket = 1;
				return; // Breaks out of handleRequest while keeping server Open
			}
			if (connect(connectionSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) != 0) {
				printf("Connection failed.\n");
				connectionSocket = 1;
				return; // Breaks out of handleRequest while keeping server Open
			}
	
			size_t length = 0;
			ssize_t lineSize;
			char* line = NULL;
			FILE *file = fopen(fileName, "r");
			while ((lineSize = getline(&line, &length, file)) != -1) {
				write(connectionSocket, line, lineSize);
			}
			free(line);
			fclose(file);
			close(connectionSocket);
			printf("File Transferred to Client\n");
			// Verification (Data) - Transfer Complete
		}
		printf("Server: FT Processed\n");
	}
	// Once request is handled, close the Client Socket
	// Verification (Data) - Connection Closed
	write(clientSocket, "/quit", 6);
}