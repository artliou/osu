/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Insertion sort implementation
//
// Downloaded from : http://www.geeksforgeeks.org/insertion-sort/
//
//

#include "SortHelpers.h"

// C program for insertion sort
#include <stdio.h>
#include <math.h>
 
/* Function to sort an array using insertion sort*/
void insertionSort(uint32_t * arr, uint32_t n)
{
   uint32_t i, key;
   int j;
   for (i = 1; i < n; i++)
   {
       key = arr[i];
       j = i-1;
 
       /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
       while (j >= 0 && arr[j] > key)
       {
           arr[j+1] = arr[j];
           j = j-1;
       }
       arr[j+1] = key;
   }
}