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

void WriteInsertionSort(uint32_t * data, const char * filename)
{
    insertionSort(&data[1], data[0]);
    std::ofstream f;
    f.open (filename, std::ofstream::out | std::ofstream::app | std::ofstream::ate);
    f << data[0] << " ";
    for(uint32_t dataPos = 1; dataPos < data[0]; dataPos++)
    {
        f << data[dataPos] << " ";
    }
    f << "\n";
}

void WriteMergeSort(uint32_t * data, const char * filename)
{
    mergeSort(&data[1], 0, data[0] - 1);
    std::ofstream f;
    f.open (filename, std::ofstream::out | std::ofstream::app | std::ofstream::ate);
    f << data[0] << " ";
    for(uint32_t dataPos = 1; dataPos < data[0]; dataPos++)
    {
        f << data[dataPos] << " ";
    }
    f << "\n";
}

float elapsedTime(struct timespec *start, struct timespec *stop)
{
    struct timespec result;
    if ((stop->tv_nsec - start->tv_nsec) < 0) {
        result.tv_sec = stop->tv_sec - start->tv_sec - 1;
        result.tv_nsec = stop->tv_nsec - start->tv_nsec + 1000000000;
    } else {
        result.tv_sec = stop->tv_sec - start->tv_sec;
        result.tv_nsec = stop->tv_nsec - start->tv_nsec;
    }

    float timeRes = result.tv_sec;
    timeRes += (result.tv_nsec / (1000000000.0f));

    return timeRes;
}