////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CS 475 - Project 1 - Numeric Integration
//
// Jeremy Prater
//

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "project3.h"
#include "CSVLogger.hpp"
#include <stdlib.h>

static const char * dataLog = "./project3.csv";
static const char * dataSchema = "numt, padding, useFix2, megaAddsSec";
static const int numArrays = 4;

typedef struct
{
	float value;
	int padding[];
} DataArray;

int main( int argc, char *argv[ ] )
{
    if (argc != 4)
    {
        printf("Incorrect number of arguments...\n");
        exit(-1);
    }

    if (CSVLogger::OpenLogFile(dataLog))
    {
        CSVLogger::WriteLog(dataSchema);
    }

    const unsigned int NUMT = atoi (argv[1]);
    const unsigned int NUMPADDING = atoi(argv[2]);
    const unsigned int USEFIX2 = atoi(argv[3]);
    const uint32_t sizeOfData = sizeof (DataArray) + (sizeof (int) * NUMPADDING);
    uint8_t * Array = (uint8_t*) malloc (numArrays * sizeOfData);

#ifndef _OPENMP
    printf("OpenMP is not supported here -- sorry.\n" );
    return 1;
#endif

    omp_set_num_threads(NUMT);
    printf("Using %d threads.\t", NUMT);
    printf("Using %d padding 32-bit ints.\t", NUMPADDING);
    printf("DataSize: %d.\t", sizeOfData);
    printf("Using Fix2: %d\t", USEFIX2);

	const int SomeBigNumber = 100000000;	// keep < 2B
    const double time0 = omp_get_wtime();
    const int loopCounter = 4;
    
	#pragma omp parallel for default(none), shared(Array)
	for(int i = 0; i < loopCounter; i++)
	{
		unsigned int seed = 0;		// automatically private
        if (USEFIX2)
        {
            // Fix #2, use private accumulator
            float tempValue = 0;
            for( unsigned int j = 0; j < SomeBigNumber; j++ )
            {
                tempValue += (float)rand_r(&seed);
            }
            // De-reference the value of Array based on padding
            (*(DataArray *)(&Array[i * sizeOfData])).value = tempValue;
        }
        else
        {
            for( unsigned int j = 0; j < SomeBigNumber; j++ )
            {
                (*(DataArray *)(&Array[i * sizeOfData])).value += (float)rand_r(&seed); 
            }
        }
	}
    
    double time1 = omp_get_wtime();
    double numAdded = SomeBigNumber * loopCounter;

    double megaAddsSec = (numAdded / (time1 - time0)) /  1000000.;

    printf ("-> NumAdded: %f\t", numAdded);
    printf ("-> megaAddsSec/sec: %f\t", megaAddsSec);
    printf ("-> Time: %f\n", time1-time0);
    CSVLogger::WriteLog("%u, %u, %u, %f", NUMT, NUMPADDING, USEFIX2, megaAddsSec);
    CSVLogger::CloseLogFile();
}


