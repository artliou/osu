// CS372
// Chat Client

// Libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>

// Resources: http://beej.us/guide/bgnet/html/single/bgnet.html

// 2) Send Message
// Grab msg from stdin and sends to sockfd ID
void* sendMessage(int sockfd){
	char username[11];
	printf("Select a username that is 10 or less characters.\n");
	scanf("%s",username);
	strcat(username, ">");
	
	char send[512];
	char msg[500];
	while (1) {
		// Erase send erase before prepping the msg
		memset(send, '\0', sizeof(send));
		// Grabbing Input and placing into 
		memset(msg, '\0', sizeof(msg));
		read(0, msg, 500);
		strcat(msg,"\0");
		// Append Username and user msg into send string
		strcpy(send,username);
		strcat(send,msg);
		// If Input was not quit then write to socket
		if (!strcmp(msg,"/quit\n")) {
			printf("Client - Chat Closed \n");
			write(sockfd, "/quit", 5);
			break;
		}
		write(sockfd, send, strlen(send) - 1);
	}
	exit(0);
	return 0;
}

// 2) Receive Message
// Grab message from socket ID
void* receiveMessage(void* socketRecID){
	int sockfd = *((int *) socketRecID);
	// Power of 2, includes 500-char message, 10-char usernamef
	char message[512];
	memset(message, '0', sizeof(message));
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
* Combined from Beej's Guide the broadcaster.c file
***/
int main(int argc, char *argv[]) {
	// Edge Case for Correct Number of Arguments on the Cmd Line
	if (argc != 3){
		printf("Error: Invalid arguments.\n");
		exit(0);
	}
	// Grabs host and port
	char* host = argv[1];
	int serverPort = atoi(argv[2]);
	// Create a socket
	struct sockaddr_in server_addr;
	struct hostent *server;
	
	int socketFD = socket(AF_INET,SOCK_STREAM,0);
	if (socketFD < 0) {
		printf("Client - Socket Connection failed...\n");
		exit(1);
		return 1;
	}
	memset(&server_addr, '0', sizeof(server_addr));
	server_addr.sin_family = AF_INET; // host byte order
	server_addr.sin_port = htons(serverPort);  // short, network byte order
	// server_addr.sin_addr = *((struct in_addr *)server->h_addr);

	// Convert IPv4 and IPv6 addresses from text to binary form
  if(inet_pton(AF_INET, host, &server_addr.sin_addr) <= 0) {
		printf("Client: Socket Connection Failed: Address not supported \n");
		return -1;
  }

	if(connect(socketFD, (struct sockaddr *)&server_addr, sizeof(server_addr)) != 0) {
		fprintf(stderr, "Client -> Server Connection Failed.\n");
		return -1;
	}
	//Thread for Receiving Messages
	pthread_t receiveID;
	pthread_create(&receiveID, NULL, receiveMessage, (void *) &socketFD);
	// Calls on Send Messages
	sendMessage(socketFD);
	//closes socket upon completion
	close(socketFD);	
	return 0;
}
