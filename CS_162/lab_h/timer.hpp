/*********************************************************************
** Author:       Jeremy Prater
** Date:         August 12, 2016
** Description:  timer.hpp
**
*********************************************************************/

#ifndef SORT_TIMER_HPP
#define SORT_TIMER_HPP

#include <time.h>

/////////////////////////////////////////////////
//
// class SortTimer
//
// A class for recording start and stop times
// and measuring the difference
//

class SortTimer
{
private:
    struct timespec start, end;

public:
    void Start();
    void Stop();
    struct timespec GetElapsed();
};

#endif // SORT_TIMER_HPP