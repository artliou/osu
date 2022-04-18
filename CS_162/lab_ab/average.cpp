/*********************************************************************
 ** Program Filename: average.cpp
 ** Description: Defines function to calculate average.
 ** Input: Array and size of array.
 ** Output: Average.
 *********************************************************************/

#include "average.h"

/*********************************************************************
 ** Function: avg
 ** Description: Calculates average of an array.
 ** Parameters: Constant double array, integer for size of array.
 ** Pre-Conditions: Array must be created to call this function.
 ** Post-Conditions: Calculated average is returned as a double type.
 *********************************************************************/

double avg(const double array[], int size)
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
    // This function duplicates code from sum()
    // This should re-written to call sum, instead of copy-paste sum code
    //
    //////////////////////

    double sum = 0.;                     /* holds sum calcualation*/
    double average;                 /* holds average calculation*/

    for(int i = 0; i < size; i++)
        sum += array[i];

    average = sum/size;

    return average;
}
