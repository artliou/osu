/*********************************************************************
** Author:       Jeremy Prater
** Date:         June 21, 2016
** Description:  Lab Aa
*********************************************************************/

#ifndef SUMMATION_H
#define SUMMATION_H

/*********************************************************************
** Description: Lab Aa average.cpp
**
** Function declarations for average.cpp
**
*********************************************************************/

/////////////////////////////////////////////////////////////////
//
// double sum (double * arrayPtr, unsigned int arrayLength)
//
// return the sum of an array of doubles.
//

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

double sum(const double * arrayPtr,const unsigned int arrayLength);

#endif // SUMMATION_H
