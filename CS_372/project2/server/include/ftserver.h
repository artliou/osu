#ifndef FTSERVER_H
#define FTSERVER_H

#include <stdint.h>

typedef struct
{
    uint16_t dataPort;
    uint16_t payloadLength;
    uint16_t hostnameLength;
    uint8_t command;
    char payload[];
} ftserverCommandHeader;

#endif // FTSERVER_H