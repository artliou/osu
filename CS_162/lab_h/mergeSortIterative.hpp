#ifndef MERGE_SORT_ITERATIVE
#define MERGE_SORT_ITERATIVE

/*********************************************************************
** Author:       Jeremy Prater
** Date:         August 12, 2016
** Description:  mergeSort_recursive.hpp
**
** Source code downloaded from :
** http://www.geeksforgeeks.org/iterative-merge-sort/
**
** Code adapted and added to a class
**
*********************************************************************/

class mergeSortIterate
{
private:
    int * buffer;
    int bufferSize;

    int merge_sort(int * arr,int n);
    void merge(int arr[], int l, int m, int r);   

public:
    mergeSortIterate(int * buffer, int bufferSize);

    void mergeSort();
};


#endif // MERGE_SORT_ITERATIVE