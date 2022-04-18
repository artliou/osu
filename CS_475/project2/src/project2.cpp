////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CS 475 - Project 1 - Numeric Integration
//
// Jeremy Prater
//

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "project2.h"
#include "CSVLogger.hpp"

static const char * dataLog = "./project2.csv";
static const char * dataSchema = "numt, mode, chunksize";

static const unsigned int ARRAYSIZE = (32 * 1024);
static long int numMuled = (long int)ARRAYSIZE * (long int)(ARRAYSIZE-1) / 2;

static float Array[ARRAYSIZE];

float fRand(float low, float high)
{
	int r = (float)rand();		// 0 - RAND_MAX
	return (((float)r/(float)RAND_MAX) * ( high-low)) + low;
}

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

    unsigned int NUMT = atoi (argv[1]);
    const char * MODE = argv[2];
    unsigned int CHUNKSIZE = atoi (argv[3]);

#ifndef _OPENMP
    printf("OpenMP is not supported here -- sorry.\n" );
    return 1;
#endif

    omp_set_num_threads(NUMT);
    printf("Using %d threads.\t", NUMT);

    /////////////////////////////////////////////////////////
    //
    // Generate array of data
    // Might as well parallize this also to speed up!
    //

    #pragma omp parallel for default(none), shared(Array)
    for(unsigned int index = 0; index < ARRAYSIZE; index++)
    {
        float num = fRand(-1., 1.);
        Array[index] = num;
    }


    printf("%s scheduling.\tChunksize: %u\t", MODE, CHUNKSIZE);
    
    omp_sched_t schedType = omp_sched_auto;
    if (strcmp (MODE, "static") == 0)
    {
        schedType = omp_sched_static;
    }
    else if (strcmp (MODE, "dynamic") == 0)
    {
        schedType = omp_sched_dynamic;
    }
    else
    {
        exit (-1);
    }

    double time0 = omp_get_wtime();
    double prod = 1.0f;
  
    omp_set_schedule(schedType, CHUNKSIZE);

    // Keep outer loop static...
    if (schedType == omp_sched_static)
    {
        omp_set_dynamic(0);
    }

    #pragma omp parallel for default(none) shared(Array) shared(schedType) reduction (*:prod)
    for (unsigned int outerLoop = 0; outerLoop < ARRAYSIZE; outerLoop++)
    {
        prod = 1.0f;

        // Set inner loop to dynamic if we are in dynamic mode
        if (schedType == omp_sched_static)
        {
            omp_set_dynamic(1);
        }
        
        #pragma omp parallel for default(none) shared(Array) shared(outerLoop) reduction (*:prod)
        for (unsigned int innerLoop = 0; innerLoop < outerLoop; innerLoop++)
        {
            prod *= Array[innerLoop];
        }

        // Reset dynamic mode since we are done with it...
        if (schedType == omp_sched_static)
        {
            omp_set_dynamic(0);
        }

    }
    double megaMultsSec = ((double)numMuled / (omp_get_wtime() - time0)) /  1000000.;

    printf ("-> MegaMults/sec: %f\t", megaMultsSec);
    printf ("-> Product: %e\n", prod);
    CSVLogger::WriteLog("%u, %u, %s, %f, %f", NUMT, CHUNKSIZE, MODE, megaMultsSec, prod);
    CSVLogger::CloseLogFile();
}


