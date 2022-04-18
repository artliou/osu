/////////////////////////////////////////////////////////////////////
//
// CS 372 Project 1
//
// Chat client
//
// Jeremy Prater
//

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <string>
#include <iostream>

/////////////////////////////////////////////////////////////////////
//
// Critical Error function
// Prints error, and exits with failure.
//

void CriticalError(const char *errorMessage)
{
    printf ("Error! [%s]\n", errorMessage);
    exit (-1);
}

/////////////////////////////////////////////////////////////////////
//
// Get Users Handle
//

std::string GetUserHandle()
{
    std::string handle;
    printf ("Enter handle : ");

    std::getline(std::cin, handle);
    handle = handle.substr (0,10);
    return handle;
}

/////////////////////////////////////////////////////////////////////
//
// Create a TCP socket for communication with the server
//

int CreateSocket()
{
    int sock;
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        CriticalError("socket() failed");
    }
    return sock;
}

/////////////////////////////////////////////////////////////////////
//
// Setup a sockaddr_in structure based on the host and port
//

struct sockaddr_in SetupConnection(char * serverHost, unsigned short serverPort)
{
    struct sockaddr_in serverAddress;

    struct hostent * hostEntry = gethostbyname(serverHost);

    if (!hostEntry)
    {
        CriticalError(hstrerror(h_errno));
    }

    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family      = AF_INET;
    serverAddress.sin_addr.s_addr = *(uint32_t*)hostEntry->h_addr_list[0];
    serverAddress.sin_port        = htons(serverPort);

    return serverAddress;
}

/////////////////////////////////////////////////////////////////////
//
// Connect to the server and send the handle
//

void ConnectToChat(int socket, struct sockaddr_in serverAddress, std::string handle)
{
    if (connect(socket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0)
    {
        CriticalError("connect() failed");
    }
    if (send(socket, handle.c_str(), handle.length(), 0) != handle.length())
    {
        CriticalError("handle sent a different number of bytes than expected");
    }
}

/////////////////////////////////////////////////////////////////////
//
// Main chat loop
//

void ChatLoop(int socket, std::string handle)
{
    std::string outgoing;
    char incomingData[1024];
    char running = 1;

    while (running)
    {
        std::cout << handle.c_str() << ">";

        std::getline(std::cin, outgoing);
        if (send(socket, outgoing.c_str(), outgoing.length(), 0) != outgoing.length())
        {
            CriticalError("send() sent a different number of bytes than expected");
        }
        if (outgoing.compare("\\quit") == 0)
        {
            std::cout << "Thanks for chatting!" << std::endl;
            running = 0;
        }
        else
        {
            memset (incomingData, 0, sizeof (incomingData));
            if (read(socket, incomingData, 1024))
            {
                if (strcmp("\\quit", incomingData + 8) == 0)
                {
                    std::cout << "Server terminated connection" << std::endl;
                    std::cout << "Thanks for chatting!" << std::endl;
                    running = 0;
                }
                else
                {
                    std::cout << incomingData << std::endl;
                }
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////
//
// Program entry point
//

int main(int argc, char *argv[])
{
    unsigned short serverPort;
    char *serverHost;

    // Ensure we have a host and port name as arguments!
    if (argc != 3)
    {
       fprintf(stderr, "Usage: %s <Server IP> <Server Port>\n", argv[0]);
       exit(-1);
    }

    // Get the host and port from the command line
    serverHost = argv[1];
    serverPort = atoi(argv[2]);
    
    // Create the TCP socket
    int socket = CreateSocket();
    
    // Get the connection information for the host and port
    struct sockaddr_in serverAddress = SetupConnection (serverHost, serverPort);
    
    // Ask user for their handle
    std::string handle = GetUserHandle();
    
    // Print a message
    printf ("Connecting to %s:%d\n", serverHost, serverPort);
    
    // Conect to the server and send handle
    ConnectToChat (socket, serverAddress, handle);
    
    // Execute main chat loop
    ChatLoop(socket, handle);

    // Close socket and exit successfully
    close(socket);
    exit(0);
}