//////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CS 344 - Assignment 4 - OTP
// Jeremy Prater
//
// Common functions header file
//

#ifndef OTP_COMMON
#define OTP_COMMON

#include <stdint.h>

#define OTP_ENC_MAGIC 0xCAFEBABE
#define OTP_DEC_MAGIC 0xDEADBEEF

void TransformInput (uint8_t * data, uint32_t size);
void TransformOutput (uint8_t * data, uint32_t size);

uint8_t * PreformOTP(uint8_t * keyData, uint8_t * fileData, uint32_t keyDataSize);

void HandleServerConnection(int serverConnection, uint32_t serverMagic, uint32_t clientMagic);
void CreateServer (int argc, char * argv[], uint32_t serverMagic, uint32_t clientMagic);

void GetServerResponse(int argc, char *argv[], uint32_t serverMagic, uint32_t clientMagic);

uint8_t * GetDataRecvLoop(int socket, uint32_t size);
uint8_t * SendDataLoop(int socket, uint8_t * data, uint32_t size);

#endif // OTP_COMMON