//////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CS 344 - Assignment 4 - OTP
// Jeremy Prater
//
// otp_enc
//

#include "common.h"

int main(int argc, char *argv[])
{
    // Get server response from OTP_ENC_MAGIC
    GetServerResponse(argc, argv, OTP_ENC_MAGIC, OTP_ENC_MAGIC);
	return 0;
}

