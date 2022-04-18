//////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CS 344 - Assignment 4 - OTP
// Jeremy Prater
//
// otp_dec_d
//

#include <stdint.h>
#include <memory.h>
#include <stdlib.h>
#include "common.h"

int main (int argc, char * argv[])
{
    CreateServer(argc, argv, OTP_DEC_MAGIC, OTP_DEC_MAGIC);
    exit(0);
}

///////////////////////////////////////////////////////////////
//
// OTP Decryption
//

uint8_t * PreformOTP(uint8_t * keyData, uint8_t * fileData, uint32_t keyDataSize)
{
    int8_t * resultData = (int8_t *)malloc(keyDataSize);
    uint32_t index = 0;
    for ( index = 0; index < keyDataSize; index++)
    {
        resultData[index] = fileData[index] - keyData[index];
        while (resultData[index] < 0)
        {
            resultData[index] += 27;
        }
    }
    return (uint8_t*)resultData;
}