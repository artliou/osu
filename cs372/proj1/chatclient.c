// Arthur Liou
// CS372
// Chat Client - C. This is the client side of a chat application

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

// Resources: http://beej.us/guide/bgnet/html/single/bgnet.html

// 2) Send Message
// Grab message from stdin and sends to sockfd ID
void* sendMessage(int sockfd) {
	//Grabs Username from stdin
	char username[10];
	printf("Select a username that is 10 or less characters.\n");
	scanf("%s",username);
	
	// create buffer for sending and for the message received
	char buffer[512];
	char message[500];
	// Similar to Server, stay in while loop until we get the quit cmd
	while (1) {
		// Erase send erase before prepping the message
		memset(buffer, '\0', sizeof(buffer));
		// Grabbing Input and placing into message
		memset(message, '\0', sizeof(message));
		// Read Message from Server
		read(0, message, 500);
		strcat(message, "\0");
		// Append Username, >, and user message into send string
		strcpy(buffer,username);
		strcat(buffer, ">");
		strcat(buffer,message);
		// If message was quit, then send quit & break out of loop
		if (!strcmp(message,"/quit\n")) {
			printf("Client - Chat Closed \n");
			write(sockfd, "/quit", 5);
			break;
		}
		// Otherwise send regular message
		write(sockfd, buffer, strlen(buffer) - 1);
	}
	exit(0);
	return 0;
}

// 2) Receive Message
// Grab message from socket ID
void* receiveMessage(void* socketRecID){
	// Resource: https://stackoverflow.com/questions/26847380/typecasting-integer-to-pointer-to-integer-in-c
	// int sockfd = (int *) socketRecID; This is not possible because incompatible pointer to integer conversion initializing 'int' with an expression of type 'void *'
	int sockfd = *(int *) socketRecID;
	// Buffer to Receive Message; similar to message[512] above
	char message[512];
	memset(message, '0', sizeof(message));
	// If message was quit, then send quit & break out of loop
	while (1) {
		read(sockfd,message,512);
		if (!strcmp(message, "/quit\0")){
			printf("\nServer - Chat Closed\n");
			write(sockfd, "/quit", 5);
			break;
		}
		printf("%s\n", message);
	}
	exit(0);
	return 0;
}

/***
* 1) Initiate Contact & Main
* Combined from Beej's Guide the broadcaster.c file & creating a p_thread
***/
int main(int argc, char *argv[]) {
	// Edge Case for Correct Number of Arguments on the Cmd Line
	if (argc != 3){
		printf("Error: Invalid arguments.\n");
		exit(0);
	}
	// Grabs host and port
	char* host = argv[1];
	int port = atoi(argv[2]);
	// Create a socket
	struct sockaddr_in server_addr;
	struct hostent *server;
	
	int socketFD = socket(AF_INET,SOCK_STREAM,0);
	if (socketFD == -1) {
		perror("socket");
		exit(1);
	}
	memset(&server_addr, '0', sizeof(server_addr));
	server_addr.sin_family = AF_INET; // host byte order
	server_addr.sin_port = htons(port);  // short, network byte order
	// server_addr.sin_addr = *((struct in_addr *)server->h_addr);

	// Convert IP addresses from text to binary form
  if(inet_pton(AF_INET, host, &server_addr.sin_addr) <= 0) {
		printf("Client: Socket Connection Failed: Address not supported \n");
		exit(1);
  }

	if(connect(socketFD, (struct sockaddr *)&server_addr, sizeof(server_addr)) != 0) {
		fprintf(stderr, "Client -> Server Connection Failed.\n");
		exit(1);
	}
	//Create a separate thread for Receiving Messages
	pthread_t receiveID;
	pthread_create(&receiveID, NULL, receiveMessage, (void *) &socketFD);
	// Calls on Send Messages
	sendMessage(socketFD);
	//closes socket upon completion
	close(socketFD);	
	return 0;
}
