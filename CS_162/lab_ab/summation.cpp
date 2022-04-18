/*********************************************************************
 ** Program Filename: summation.cpp
 ** Description: Defines function to calculate sum.
 ** Input: Array and size of array.
 ** Output: Sum.
 *********************************************************************/

#include "summation.h"

/*********************************************************************
 ** Function: sum
 ** Description: Calculates sum of an array.
 ** Parameters: Constant double array, integer for size of array.
 ** Pre-Conditions: Array must be created to call this function.
 ** Post-Conditions: Calculated sum is returned as a double type.
 *********************************************************************/

double sum(const double array[], int size)
{
    //////////////////////
    //
    // Added By Jeremy Prater
    //
    if (size == 0)
        return 0;
    if (array == __null)
        return 0;
    //
    //
    //////////////////////

    double sum = 0.;                     /* holds sum calculation*/

    for(int i = 0; i < size; i++)
        sum += array[i];

    return sum;
}
