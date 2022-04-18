/*********************************************************************
** Author:       Jeremy Prater
** Date:         June 21, 2016
** Description:  Lab Aa
*********************************************************************/
#include "average.h"

/*********************************************************************
** Description: Lab Aa average.cpp
**
** Implementation for average.cpp
**
*********************************************************************/

/////////////////////////////////////////////////////////////////
//
// double avg (double * arrayPtr, unsigned int arrayLength)
//
// return the average of an array of doubles.
//

double avg(const double * arrayPtr,const unsigned int arrayLength)
{
  // Declare a local double for the average.
  double arrayAvg = 0;

  if ((arrayLength == 0) || (arrayPtr == 0))
  {
    // If the length is 0, return the default value of 0
    // If the arrayPtr is invalid (null), return default value of 0
    return arrayAvg;
  }
  
  // Get the summation of the array and divide by length to get the average;
  arrayAvg = sum (arrayPtr, arrayLength) / arrayLength;

  // Return the result
  return arrayAvg;
}
