#ifndef FTSERVER_DATA_H
#define FTSERVER_DATA_H

#include <stdint.h>

uint8_t * GetServerResponse(const char * host, uint16_t clientPort, uint8_t command, const char * file);

#endif // FTSERVER_DATA_H