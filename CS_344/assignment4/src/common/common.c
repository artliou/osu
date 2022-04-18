//////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CS 344 - Assignment 4 - OTP
// Jeremy Prater
//
// Common functions (otp_enc/otp_dec)
//

#include "common.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>


/////////////////////////////////////////////////////////////
//
// Transform input from [' ', ['A', 'Z']] into ['A', '[']
//

void TransformInput (uint8_t * data, uint32_t size)
{
    uint32_t index = 0;
    for (index = 0; index < size; index++)
    {
        if (data[index] == 0x20)
        {
            data[index] = 0x5B;
        }
        data[index] -= 0x41;
    }
}

/////////////////////////////////////////////////////////////
//
// Transform result from ['A', 'Z'] into [' ', ['A', 'Z']]
//

void TransformOutput (uint8_t * data, uint32_t size)
{
    uint32_t index = 0;
    for (index = 0; index < size; index++)
    {
        data[index] += 0x41;
        if (data[index] == 0x5B)
        {
            data[index] = 0x20;
        }
    }
}

/////////////////////////////////////////////////////////////
//
// TCP send/recv data loops.
//
// Break large chunks into smaller send/recv request
//

uint8_t * GetDataRecvLoop(int socket, uint32_t size)
{
    uint8_t * payload = (uint8_t *)malloc(size);
    uint32_t offset = 0;
    //fprintf (stderr, "[%d] -- Server Recv Start [%d]\n", getpid(), size);
    while (size > 0)
    {
        uint32_t recvSize = size;
        if (recvSize > 1000)
        {
            recvSize = 1000;
        }
        //fprintf (stderr, "[%d] -- Server Recv progress [%d]\n", getpid(), offset);
        ssize_t recvRes = recv(socket, &payload[offset], recvSize, 0);
        if (recvRes < 0)
        {
            fprintf (stderr, "[%d] Client recv data failed [%s]\n", getpid(), strerror(errno));
            exit (-errno);
        }
        else
        {
            offset += recvRes;
            size -= recvRes;
        }
    }
    //fprintf (stderr, "[%d] -- Server Recv progress [%d]\n", getpid(), offset);
    return payload;
}

uint8_t * SendDataLoop(int socket, uint8_t * data, uint32_t size)
{
    //fprintf (stderr, "[%d] -- Server Send Start [%d]\n", getpid(), size);
    uint32_t offset = 0;
    while (size > 0)
    {
        uint32_t recvSize = size;
        if (recvSize > 1000)
        {
            recvSize = 1000;
        }
        //fprintf (stderr, "[%d] -- Server Send progress [%d]\n", getpid(), offset);
        ssize_t sendRes = send(socket, &data[offset], recvSize, 0);
        if (sendRes < 0)
        {
            fprintf (stderr, "[%d] Client send data failed [%s]\n", getpid(), strerror(errno));
            exit (-errno);
        }
        else
        {
            offset += sendRes;
            size -= sendRes;
        }
    }
    //fprintf (stderr, "[%d] -- Server Send progress [%d]\n", getpid(), offset);
}
