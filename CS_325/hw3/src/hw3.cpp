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
#include <iterator>

#include "minChange.h"

static const char * dataLog = "./../hw3.csv";
static const char * dataSchema = "NUM_C,A,RUNTIME_CHANGE";

static struct timespec time0;
static struct timespec time1;

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

    const unsigned int USE_DATA = atoi(argv[1]);
    const unsigned int NUM_COINS = atoi (argv[2]);
    const unsigned int AMOUNT = atoi (argv[3]);

    //printf ("-> USE_DATA: %d\t", USE_DATA);
    //printf ("-> COINS: %d\t", NUM_COINS);
    //printf ("-> AMOUNT: %d\t", AMOUNT);

    if (USE_DATA)
    {
        // Read data from file
        // Open file
        std::ifstream fileStream ("./../data/amount.txt", std::ifstream::binary);

        std::string line;
        std::vector<coinSet_t> fileData;
        bool readMode = true;
        coinSet_t newSet;
        while (getline(fileStream, line))
        {
            if (readMode)
            {
                std::istringstream is(line);
                newSet.C = std::vector<int>(std::istream_iterator<int>(is), std::istream_iterator<int>());
            }
            else
            {
                newSet.A = stoi (line);
                fileData.push_back(newSet);
            }
            readMode = !readMode;
        }
        uint32_t loadedSets = fileData.size();
        printf ("-> Loaded Sets : %d\n", loadedSets);
        for (uint32_t currentSet = 0; currentSet < loadedSets; currentSet++)
        {
            WriteMinCoins (&fileData[currentSet], "./../change.txt");
        }
        printf ("-> Processed Sets : %d\n", loadedSets);
    }
    else
    {
        coinSet_t testSet;
        testSet.A = AMOUNT;
        testSet.C.push_back(1);
        for (int coins = 1; coins < NUM_COINS; coins++)
        {
            testSet.C.push_back(rand() % (NUM_COINS * 100));
        }

        int coinData[NUM_COINS];

        clock_gettime (CLOCK_MONOTONIC, &time0);
        minCoins(&testSet, coinData);
        clock_gettime (CLOCK_MONOTONIC, &time1);
    }

    printf ("-> RUNTIME(min-change): %f\n", elapsedTime (&time0, &time1));

    CSVLogger::WriteLog("%d, %d, %f",
        NUM_COINS,
        AMOUNT,
        elapsedTime (&time0, &time1));

    CSVLogger::CloseLogFile();
}
