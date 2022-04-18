////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CS 475 - Project 4 - Randomizer
//
// Jeremy Prater
//

#include "Randomizer.hpp"
#include <stdlib.h>
#include <time.h>

float Randomizer::Random(unsigned int *seedp, float low, float high)
{
    float r = (float)rand_r(seedp);
    return(low + r * (high - low) / (float)RAND_MAX);
}

int Randomizer::Random(unsigned int *seedp, int ilow, int ihigh)
{
    float low = (float)ilow;
    float high = (float)ihigh + 0.9999f;

    return (int)(Random(seedp, low,high));
}

unsigned int Randomizer::GetTimeBasedSeed()
{
    return (unsigned int)time(NULL);
}