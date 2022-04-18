/*********************************************************************
** Author:       Jeremy Prater
** Date:         August 12, 2016
** Description:  mergeSort_recursive.cpp
**
** Source code downloaded from :
** https://gist.github.com/codeblocks/898596
**
** Code adapted and added to a class
**
*********************************************************************/

#include "mergeSortRecursive.hpp"
#include "limits.h"
#include "stdlib.h"
#include "timer.hpp"
#include "lib_flip_display.hpp"

/**
  * Divide  : Divide the n-element array into two n/2-element
  *           sub-arrays
  * Conquer : Sort the two sub-arrays recursively using
  *           merge sort
  * Combine : Merge the two sorted subsequences to form the
  *           sorted array
  **/

mergeSortRecursive::mergeSortRecursive(int * newbuffer, int newbufferSize)
{
  buffer = newbuffer;
  bufferSize = newbufferSize;
}

void mergeSortRecursive::mergeSort()
{
  DebugConsole::debug_print (0, true, COLOR_CYAN, "Starting mergesort Recursive... %d items\n\n", bufferSize);
  SortTimer myTimer;
  myTimer.Start();
  merge_sort(buffer, 0, bufferSize);
  myTimer.Stop();
  struct timespec elapsed = myTimer.GetElapsed();
  DebugConsole::debug_print (0, true, COLOR_CYAN, "mergeSort Recursive took %d.%d\n\n", elapsed.tv_sec, elapsed.tv_nsec);
}

int mergeSortRecursive::merge_sort(int * arr,int low,int high)
{
  int mid;
  if(low<high) {
    mid=(low+high)/2;
    // Divide and Conquer
    merge_sort(arr,low,mid);
    merge_sort(arr,mid+1,high);
    // Combine
    merge(arr,low,mid,high);
  }

  return 0;
}

int mergeSortRecursive::merge(int * arr,int l,int m,int h)
{
  int n1,n2,i,j,k;
  n1=m-l+1;
  n2=h-m;

  //int * arr1 = (int*)malloc (bufferSize * sizeof(int));
  //int * arr2 = (int*)malloc (bufferSize * sizeof(int));  // Two temporary arrays to hold the two arrays to be merged
  int arr1[n1];
  int arr2[n2];

  for(i=0; i<n1; i++)
    arr1[i]=arr[l+i];
  for(j=0; j<n2; j++)
    arr2[j]=arr[m+j+1];

  arr1[i]=INT_MAX;  // To mark the end of each temporary array
  arr2[j]=INT_MAX;

  i=0;
  j=0;
  for(k=l; k<=h; k++) { //process of combining two sorted arrays
    if(arr1[i]<=arr2[j])
      arr[k]=arr1[i++];
    else
      arr[k]=arr2[j++];
  }

  //free (arr1);
  //free (arr2);
  return 0;
}