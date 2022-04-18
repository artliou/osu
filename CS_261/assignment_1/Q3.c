/* CS261- Assignment 1 - Q.3*/
/* Name: Jeremy Prater
 * Date: Sept 23, 2016
 * Solution description: Sort an array of integers
 */
 
#include <stdio.h>
#include<stdlib.h>
#include<math.h>

//////////////////////////////////////////////////////////////////////
//
// Function definitions
//
//////////////////////////////////////////////////////////////////////

int merge_sort(int * arr,int n);
void merge(int arr[], int l, int m, int r);

void sort(int* number, int n){
     /*Sort the given array number , of length n*/
     merge_sort (number, n);  
}

//////////////////////////////////////////////////////////////////////
//
// Program entry point
//
//////////////////////////////////////////////////////////////////////

int main(){
    /*Declare an integer n and assign it a value of 20.*/
    int n = 20;
    
    /*Allocate memory for an array of n integers using malloc.*/
    int * memory = (int*)malloc(sizeof(int) * n);
    
    /*Fill this array with random numbers, using rand().*/
    for (int index = 0; index < n; index++)
    {
        memory[index] = rand();
    }
    
    /*Print the contents of the array.*/
    printf ("\n -- Unsorted --\n");
    for (int index = 0; index < n; index++)
    {
        printf ("%d:\t%08x\n", index, memory[index]);
    }

    /*Pass this array along with n to the sort() function of part a.*/
    sort (memory, n);
    
    /*Print the contents of the array.*/
    printf ("\n -- Sorted --\n");    
    for (int index = 0; index < n; index++)
    {
        printf ("%d:\t%08x\n", index, memory[index]);
    }
    
    return 0;
}

//////////////////////////////////////////////////////////////////////
//
// Taken from CS_162
//
// modified to remove class dependencies

/*********************************************************************
** Author:       Jeremy Prater
** Date:         August 12, 2016
** Description:  mergeSort_Iterate.cpp
**
** Source code downloaded from :
** http://www.geeksforgeeks.org/iterative-merge-sort/
**
** Code adapted and added to a class
**
*********************************************************************/

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

///////////////////////////////////////////////////////////////////////////////
//
// Source code from : http://www.geeksforgeeks.org/iterative-merge-sort/
//

/* Iterative mergesort function to sort arr[0...n-1] */
int merge_sort(int * arr,int n)
{
   int curr_size;  // For current size of subarrays to be merged
                   // curr_size varies from 1 to n/2
   int left_start; // For picking starting index of left subarray
                   // to be merged
 
   // Merge subarrays in bottom up manner.  First merge subarrays of
   // size 1 to create sorted subarrays of size 2, then merge subarrays
   // of size 2 to create sorted subarrays of size 4, and so on.
   for (curr_size=1; curr_size<=n-1; curr_size = 2*curr_size)
   {
       // Pick starting point of different subarrays of current size
       for (left_start=0; left_start<n-1; left_start += 2*curr_size)
       {
           // Find ending point of left subarray. mid+1 is starting 
           // point of right
           int mid = left_start + curr_size - 1;
 
           int right_end = min(left_start + 2*curr_size - 1, n-1);
 
           // Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
           merge(arr, left_start, mid, right_end);
       }
   }
   return 0;
}

/* Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[] */
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];
 
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    /* Copy the remaining elements of L[], if there are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    /* Copy the remaining elements of R[], if there are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
