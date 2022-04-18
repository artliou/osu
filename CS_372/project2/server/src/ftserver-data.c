////////////////////////////////////////////////////////////////////////////////
//
// ftServer Data connection
//
// CS 372 - Project 2 - Jeremy Prater
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <memory.h>
#include <errno.h>
#include <string.h>
#include <limits.h>

////////////////////////////////////////////////////////////////////////////////
//
// Static local variables
//

static int serverSocket;
static char currentDirectory[PATH_MAX];

////////////////////////////////////////////////////////////////////////////////
//
// Send the response to the server
//

uint8_t * GetServerResponse(const char * host, uint16_t clientPort, uint8_t command, const char * file)
{
    getcwd(currentDirectory, sizeof (currentDirectory));
    printf ("Connect to ftclient [%s]:[%d]\n", host, clientPort);
    struct hostent *server;
    struct sockaddr_in serverAddress;
    int serverConnection = -1;

    memset (&serverAddress, 0, sizeof (serverAddress));

    // Create TCP socket on port
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("Failed to create TCP server socket [%s]\n\n", strerror(errno));
        exit(-errno);
    }

    // Get the ip address of the client hostname
    server = gethostbyname(host);
    if (server == NULL) {
        printf("Failed to find host [%s]\n", host);
        exit(-4);
    }

    // Setup socket address
    serverAddress.sin_family = AF_INET;
    memcpy (&serverAddress.sin_addr.s_addr, server->h_addr_list[0], server->h_length);
    serverAddress.sin_port = htons(clientPort);

    int retryCounter = 0;
    // Attempt to connect
    while (connect(serverSocket, (const struct sockaddr*)&serverAddress, sizeof (serverAddress)) < 0)
    {
        // If the connection failed, the client may not be listening on the data port yet.
        sleep(1);
        retryCounter++;
        if (retryCounter == 5)
        {
            printf("Failed to connect to ftClient [%s]\n\n", strerror(errno));
            exit(-errno);
        }
    }

    printf("Connected to data port [%s]:[%d]\n", host, clientPort);
    fflush(stdout);


    // Process the command and send the result to the connected socket
    uint32_t payloadSize = 0;

    FILE * externalProcess = NULL;
    switch (command)
    {
        case 0: // list directory
        {
            printf ("Returning directory contents of [%s]\n", currentDirectory);
            externalProcess = popen("ls -l", "r");
        }
        break;
        case 1: // Get file
        {
            externalProcess = fopen(file, "r");
        }
        break;
    }

    if (externalProcess == NULL)
    {
        // Error Stuff
        // Not implemented...
    }
    else
    {
        // Read the stdout of the external process into the socket.
        char outBuffer[1024];
        while (!feof(externalProcess))
        {
            size_t sendDataSize = fread(outBuffer, 1, 1024, externalProcess);
            send(serverSocket, outBuffer, sendDataSize, 0);
        }
    }
    if (externalProcess > 0)
    {
        fclose (externalProcess);
    }

    // Completed sending data. Close connection.
    close(serverSocket);
    printf("Disconnected from data port [%s]:[%d] arrivederci!\n", host, clientPort);
    fflush(stdout);

    return NULL;
}
