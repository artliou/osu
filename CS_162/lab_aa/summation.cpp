/*********************************************************************
** Author:       Jeremy Prater
** Date:         June 21, 2016
** Description:  Lab Aa
*********************************************************************/
#include "summation.h"

/*********************************************************************
** Description: Lab Aa summation.cpp
**
** Implementation for summation.cpp
**
*********************************************************************/

/////////////////////////////////////////////////////////////////
//
// double sum (double * arrayPtr, unsigned int arrayLength)
//
// return the sum of an array of doubles.
//

double sum(const double * arrayPtr,const unsigned int arrayLength)
{
  // Declare a local double for the average.
  double arraySum = 0;

  if ((arrayLength == 0) || (arrayPtr == 0))
  {
    // If the length is 0, return the default value of 0
    // If the arrayPtr is invalid (null), return default value of 0
    return arraySum;
  }
  
  for (unsigned int arrayPosition = 0; arrayPosition < arrayLength; arrayPosition++)
  {
    // Sum all the elements of arrayPtr
    arraySum += arrayPtr[arrayPosition];
  }
  
  // Return the result
  return arraySum;
}
