//////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CS 344 - Assignment 4 - OTP
// Jeremy Prater
//
// otp_dec
//

#include "common.h"

int main(int argc, char *argv[])
{
    // Get server response from OTP_DEC_MAGIC
    GetServerResponse(argc, argv, OTP_DEC_MAGIC, OTP_DEC_MAGIC);
	return 0;
}
