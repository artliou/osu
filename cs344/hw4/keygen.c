/***
Arthur Liou
CS344
Purpose: This File generates the encryption key to use in the OTP program
Usage Syntax: otp_enc_d listening_port
***/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
  // Edge Case to catch if arguments is less than 2
  // Print Out the Length of the arguments & exit with status of 1 (failure)
  if (argc < 2){ 
		printf("%s Keygen Error - Incorrect Number of Arguments: \n", argv[0]);
    exit(1);
	}

  //Converts the given key:Length from char type to int type
  //This is so we can iterate over the length
	int keyLength = atoi(argv[1]);

  //Char Type to hold the key itself
  char key[keyLength];
  
  //Setting up a for loop to get keyLength random letters
  // Available Characters
	char template[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";

  // Using computer's internal clock to control the choice of the seed used here for rand later
	srand(time(NULL));
  //For each keyLength index, generate a random letter @index i
  int i;
	for (i = 0; i < keyLength - 1; i++){
		key[i] = template[rand() % 27];
	}
  //null char String Terminator for key
	key[keyLength] = '\0'; 
	//Print the Key
	printf("%s \n", key);
	return 0;
}
