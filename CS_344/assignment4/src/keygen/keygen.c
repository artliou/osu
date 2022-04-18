//////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CS 344 - Assignment 4 - OTP
// Jeremy Prater
//
// Encryption key generator
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>


/////////////////////////////////////////////////////////////
//
// Generate a key of length n, with characters [' ', ['A', 'Z']]
//

int main (int argc, char * argv[])
{
    uint32_t keyLength = 0;
    if (argc != 2)
    {
        fprintf (stderr, "%s [key length]\n", argv[0]);
        return -1;
    }

    if (sscanf (argv[1], "%d", &keyLength) != 1)
    {
        fprintf(stderr, "Invalid Key Length [%s]\n\n", argv[1]);
        return -2;
    }

    // Generate key
    srand(time(NULL));
    while (keyLength > 0)
    {
        uint8_t keySegment = rand() % 27;
        if (keySegment == 26)
        {
            // It's space
            keySegment = 0x20;
        }
        else
        {
            // It's [A,Z]
            keySegment += 0x41;
        }

        printf ("%c", keySegment);
        keyLength--;
    }
    printf("\n");
    exit(0);
}