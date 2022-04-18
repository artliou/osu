////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CS 325 - Homework 1
//
// Jeremy Prater
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include "CSVLogger.hpp"
#include <time.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>

#include "SortHelpers.h"

static const char * dataLog = "./../hw2.csv";
static const char * dataSchema = "NUM_ELEMENTS,RUNTIME_Stooge,RUNTIME_INSERTION";

static struct timespec time0;
static struct timespec time1;
static struct timespec time2;

int main( int argc, char *argv[ ] )
{
    if (argc != 3)
    {
        printf("Incorrect number of arguments...\n");
        exit(-1);
    }

    if (CSVLogger::OpenLogFile(dataLog))
    {
        CSVLogger::WriteLog(dataSchema);
    }

    const unsigned int USE_DATA = atoi(argv[1]);
    const unsigned int NUM_ELEMENTS = atoi (argv[2]);

    printf ("-> USE_DATA: %d\t", USE_DATA);
    printf ("-> ELEMENTS: %d\t", NUM_ELEMENTS);

    float runTimeStooge = 0.0f;
    float runTimeInsert = 0.0f;

    if (USE_DATA == 1)
    {
        // Read data from file
        // Open file
        std::ifstream fileStream ("./../data/data.txt", std::ifstream::binary);

        std::string line;
        std::vector<std::vector<uint32_t> > fileData;
        while (getline(fileStream, line))
        {
            std::istringstream is(line);
            fileData.push_back(
                std::vector<uint32_t>(std::istream_iterator<uint32_t>(is),
                    std::istream_iterator<uint32_t>()));
        }
        uint32_t loadedSets = fileData.size();
        printf ("-> Loaded Sets : %d\t", loadedSets);
        for (uint32_t currentSet = 0; currentSet < loadedSets; currentSet++)
        {
            WriteInsertionSort (fileData[currentSet].data(), "./../insert.out");
            WriteStoogeSort (fileData[currentSet].data(), "./../stooge.out");
        }
        printf ("-> Processed Sets : %d\n", loadedSets);
        return 0;
    }
    else
    {
        // Generate data based on NUM_ELEMENTS
        uint32_t * insertionSortData;
        uint32_t * StoogeSortData;
        insertionSortData = (uint32_t*)malloc (sizeof (uint32_t) * NUM_ELEMENTS);
        StoogeSortData = (uint32_t*)malloc (sizeof (uint32_t) * NUM_ELEMENTS);
        for (uint32_t dataPosition = 0; dataPosition < NUM_ELEMENTS; dataPosition++)
        {
            insertionSortData[dataPosition] = StoogeSortData[dataPosition] = rand();
        }
        clock_gettime (CLOCK_MONOTONIC, &time0);
        insertionSort(insertionSortData, NUM_ELEMENTS);
        clock_gettime (CLOCK_MONOTONIC, &time1);
        stoogeSort(StoogeSortData, 0, NUM_ELEMENTS - 1);
        clock_gettime (CLOCK_MONOTONIC, &time2);

        runTimeInsert = elapsedTime (&time0, &time1);
        runTimeStooge = elapsedTime (&time1, &time2);

        free (insertionSortData);
        free (StoogeSortData);
    }

    printf ("-> RUNTIME(insert): %f\t", runTimeInsert);
    printf ("-> RUNTIME(Stooge): %f\n", runTimeStooge);

    CSVLogger::WriteLog("%d, %f, %f",
        NUM_ELEMENTS,
        runTimeStooge,
        runTimeInsert);


    CSVLogger::CloseLogFile();

}
