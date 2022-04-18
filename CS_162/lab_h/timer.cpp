/*********************************************************************
** Author:       Jeremy Prater
** Date:         August 12, 2016
** Description:  timer.cpp
**
*********************************************************************/

#include <time.h>
#include "timer.hpp"

///////////////////////////////////////////////////////////////////////////////
//
// void SortTimer::Start()
//
// Record the start time for the timer
//
// Parameters:
//        None
//
// Return:
//        None
//

void SortTimer::Start()
{
	clock_gettime (CLOCK_REALTIME, &start);
}

///////////////////////////////////////////////////////////////////////////////
//
// void SortTimer::Stop()
//
// Record the start time for the timer
//
// Parameters:
//        None
//
// Return:
//        None
//

void SortTimer::Stop()
{
	clock_gettime (CLOCK_REALTIME, &end);
}

///////////////////////////////////////////////////////////////////////////////
//
// struct timespec SortTimer::GetElapsed()
//
// Calculate the time difference between start and stop
//
// Parameters:
//        None
//
// Return:
//        struct timespec - difference between start and stop.
//

struct timespec SortTimer::GetElapsed()
{
	timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}