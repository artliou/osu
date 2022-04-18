#ifndef MERGE_SORT_RECURSIVE
#define MERGE_SORT_RECURSIVE

/*********************************************************************
** Author:       Jeremy Prater
** Date:         August 12, 2016
** Description:  mergeSort_recursive.hpp
**
** Source code downloaded from :
** https://gist.github.com/codeblocks/898596
**
** Code adapted and added to a class
**
*********************************************************************/



/**
  * Divide  : Divide the n-element array into two n/2-element
  *           sub-arrays
  * Conquer : Sort the two sub-arrays recursively using
  *           merge sort
  * Combine : Merge the two sorted subsequences to form the
  *           sorted array
  **/

class mergeSortRecursive
{
private:
    int * buffer;
    int bufferSize;

    int merge_sort(int * arr,int low,int high);
    int merge(int * arr,int l,int m,int h);   

public:
    mergeSortRecursive(int * buffer, int bufferSize);

    void mergeSort();
};


#endif // MERGE_SORT_RECURSIVE