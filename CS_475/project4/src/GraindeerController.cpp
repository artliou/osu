////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CS 475 - Project 4 - Graindeer Controller
//
// Jeremy Prater
//
// Processing Threads
//

#include "GraindeerController.hpp"
#include "Randomizer.hpp"
#include "CSVLogger.hpp"
#include <math.h>
#include <time.h>
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Graindeer Controller Static Variables
//

const float GraindeerController::GRAIN_GROWS_PER_MONTH   = 8.0;
const float GraindeerController::ONE_DEER_EATS_PER_MONTH = 0.5;

const float GraindeerController::AVG_PRECIP_PER_MONTH    = 6.0;	// average
const float GraindeerController::AMP_PRECIP_PER_MONTH    = 6.0;	// plus or minus
const float GraindeerController::RANDOM_PRECIP           = 2.0;	// plus or minus noise

const float GraindeerController::AVG_TEMP                = 50.0;	// average
const float GraindeerController::AMP_TEMP                = 20.0;	// plus or minus
const float GraindeerController::RANDOM_TEMP             = 10.0;	// plus or minus noise

const float GraindeerController::MIDTEMP                 = 40.0;
const float GraindeerController::MIDPRECIP               = 10.0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Graindeer Controller Constructor
//

GraindeerController::GraindeerController()
{
}

GraindeerController::~GraindeerController()
{
}

void GraindeerController::SetInitialState(SystemState * state)
{
    // starting date and time:
    state->NowMonth   = 0;
    state->NowYear    = 2017;

    // starting state (feel free to change this if you want):
    state->NowNumDeer = 1;
    state->NowHeight  = 1.;

    // Random Events
    state->NowFlood   = false;
    state->NowFire    = false;

    unsigned int seed = (unsigned int)time(NULL);  // a thread-private variable
    UpdateTempPrecip (state, &seed);

    // Threads are running!
    state->NowRunning = true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Graindeer Controller Update functions
//

void GraindeerController::UpdateTempPrecip(SystemState * state, unsigned int * seed)
{
    float ang = (30. * (float)state->NowMonth + 15) * ( M_PI / 180. );

    float temp = AVG_TEMP - AMP_TEMP * cos( ang );
    state->NowTemp = temp + Randomizer::Random(seed, -RANDOM_TEMP, RANDOM_TEMP );

    float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
    state->NowPrecip = precip + Randomizer::Random(seed,  -RANDOM_PRECIP, RANDOM_PRECIP );
    if(state->NowPrecip < 0.)
    {
        state->NowPrecip = 0.;
    }
}

float GraindeerController::SQR(float value)
{
    return (value * value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Graindeer Controller Thread Functions
//

void GraindeerController::GrainDeer(SystemState * systemState)
{
    unsigned int seed = (unsigned int)time(NULL);  // a thread-private variable
    while(systemState->NowRunning)
    {
        int newDeer = systemState->NowNumDeer;
        if (systemState->NowNumDeer < systemState->NowHeight)
        {
            newDeer++;
        }

        if (systemState->NowNumDeer > systemState->NowHeight)
        {
            newDeer--;
        }

        if (systemState->NowFlood)
        {
            newDeer = 0;
        }

        #pragma omp barrier // DoneComputing barrier

        systemState->NowNumDeer = newDeer;
        #pragma omp barrier // DoneAssigning barrier
        #pragma omp barrier // DonePrinting barrier
    }
}

void GraindeerController::GrainGrowth(SystemState * systemState)
{
    unsigned int seed = (unsigned int)time(NULL);  // a thread-private variable
    while(systemState->NowRunning)
    {
        float tempFactor = exp(-GraindeerController::SQR((systemState->NowTemp - MIDTEMP)/10.));
        float precipFactor = exp(-GraindeerController::SQR((systemState->NowPrecip - MIDPRECIP)/10.));
        float newHeight = systemState->NowHeight;

        if (systemState->NowFlood)
        {
            newHeight *= 2;
        }

        if (systemState->NowFire)
        {
            newHeight = 0;
        }
        else
        {
            newHeight += tempFactor * precipFactor * GRAIN_GROWS_PER_MONTH;
            newHeight -= (float)systemState->NowNumDeer * ONE_DEER_EATS_PER_MONTH;
        }

        if (newHeight < 0)
        {
            newHeight = 0;
        }

        #pragma omp barrier // DoneComputing barrier


        systemState->NowHeight = newHeight;
        #pragma omp barrier // DoneAssigning barrier
        #pragma omp barrier // DonePrinting barrier
    }
}

void GraindeerController::Watcher(SystemState * systemState)
{
    unsigned int seed = (unsigned int)time(NULL);  // a thread-private variable
    while(systemState->NowRunning)
    {
        #pragma omp barrier // DoneComputing barrier
        #pragma omp barrier // DoneAssigning barrier
        CSVLogger::WriteLog("%f, %f, %f, %f, %d, %d, %d",
            (float)systemState->NowYear + ((float)systemState->NowMonth / 12.),
            (5./9.)*(systemState->NowTemp-32.),
            systemState->NowPrecip * 2.54,
            systemState->NowHeight,
            systemState->NowNumDeer,
            systemState->NowFire * 30,
            systemState->NowFlood * 30);


        printf ("Date : [%02d-%04d]\tTemp : %.2f\tPrecip : %.2f\tHeight : %.2f\tGraindeer : %d\tFire : %d\tFlood : %d\n",
            systemState->NowMonth,
            systemState->NowYear,
            (5./9.)*(systemState->NowTemp-32.),
            systemState->NowPrecip * 2.54,
            systemState->NowHeight,
            systemState->NowNumDeer,
            systemState->NowFire * 30,
            systemState->NowFlood * 30);

        if (++systemState->NowMonth == 12)
        {
            systemState->NowMonth = 0;
            if (++systemState->NowYear == 2023)
            {
                systemState->NowRunning = false;
            }
        }

        UpdateTempPrecip(systemState, &seed);
        #pragma omp barrier // DonePrinting barrier
    }
}

void GraindeerController::UnknownEvents(SystemState * systemState)
{
    unsigned int seed = (unsigned int)time(NULL);  // a thread-private variable
    while(systemState->NowRunning)
    {
        bool newFire = systemState->NowHeight > 35.;
        bool newFlood = (Randomizer::Random(&seed,  0, 100) > 95);
        #pragma omp barrier // DoneComputing barrier

        systemState->NowFlood = newFlood;
        systemState->NowFire = newFire;
        #pragma omp barrier // DoneAssigning barrier
        #pragma omp barrier // DonePrinting barrier
    }
}