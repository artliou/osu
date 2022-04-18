////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CS 475 - Project 4 - Control Threads
//
// Jeremy Prater
//
// Random Number Generator
//

#ifndef PROJECT4_RANDOMIZER_H
#define PROJECT4_RANDOMIZER_H

class Randomizer
{
public:
    static int   GetTimeBasedSeed();
    static float Random(unsigned int *seedp, float low, float high);
    static int   Random(unsigned int *seedp, int ilow, int ihigh);
};

#endif // PROJECT4_RANDOMIZER_H
