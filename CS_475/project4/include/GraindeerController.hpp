////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CS 475 - Project 4 - Control Threads
//
// Jeremy Prater
//
// Main Header
//

#ifndef PROJECT4_GRAINDEER_CONTROLLER_H
#define PROJECT4_GRAINDEER_CONTROLLER_H

#include "project4.hpp"

class GraindeerController
{
public:
    GraindeerController();
    ~GraindeerController();

    static const float GRAIN_GROWS_PER_MONTH;
    static const float ONE_DEER_EATS_PER_MONTH;

    static const float AVG_PRECIP_PER_MONTH;	// average
    static const float AMP_PRECIP_PER_MONTH;	// plus or minus
    static const float RANDOM_PRECIP;	        // plus or minus noise

    static const float AVG_TEMP;	            // average
    static const float AMP_TEMP;	            // plus or minus
    static const float RANDOM_TEMP;        	// plus or minus noise

    static const float MIDTEMP;
    static const float MIDPRECIP;

    static void SetInitialState(SystemState * state);
    static void UpdateTempPrecip(SystemState * state, unsigned int * seed);

    static float SQR(float value);

    static void GrainDeer(SystemState * state);
    static void GrainGrowth(SystemState * state);
    static void Watcher(SystemState * state);
    static void UnknownEvents(SystemState * state);
};

#endif // PROJECT4_GRAINDEER_CONTROLLER_H
