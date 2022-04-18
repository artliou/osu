/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Insertion sort implementation
//
// Downloaded from : http://www.geeksforgeeks.org/insertion-sort/
//
//

#include "SortHelpers.h"

// C program for insertion sort
#include <math.h>
#include <stdio.h>

// Use static for local functions
static void swap (uint32_t * a, uint32_t * b)
{
    uint32_t c = *a;
    *b = *a;
    *a = c;
}

/* Function to sort an array using stooge sort*/
void stoogeSort(uint32_t * arr, uint32_t start, uint32_t end)
{
    if (end < start)
    {
        return;
    }
    
    uint32_t n = end - start;
    
    if ((n == 2) && (arr[start] > arr[start + 1]))
    {
        swap (&arr[start], &arr[start + 1]);
    }
    else if (n > 2)
    {
        int32_t m = ceil(2*(end)/3);
        if (m < 1)
        {
            m=1;
        }
        stoogeSort(arr, start, m - 1);     //A[0 ... m - 1]
        stoogeSort(arr, n - m, end - 1); //A[n - m ... n - 1]
        stoogeSort(arr, start, m - 1);     //A[0 ... m - 1])
    }
}