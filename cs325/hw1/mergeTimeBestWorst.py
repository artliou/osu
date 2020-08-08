# Merge Sort for CS325 HW1
# Time: O(nlogn)
# Space: O(n)

import time
import random

#define mergesort function
def mergeSort(listToMerge):
    # Console output to confirm our inputs
    # print("MergeSorting: ",listToMerge)

    if len(listToMerge)>1:
        mid = len(listToMerge)//2
        lefthalf = listToMerge[:mid]
        righthalf = listToMerge[mid:]

        # Recursion
        mergeSort(lefthalf)
        mergeSort(righthalf)

        # Define Variables to Help Sort
        i=0
        j=0
        k=0

        # Sorting Each Half of the List, to be then mergesorted again
        while i < len(lefthalf) and j < len(righthalf):
            if lefthalf[i] < righthalf[j]:
                listToMerge[k]=lefthalf[i]
                i=i+1
            else:
                listToMerge[k]=righthalf[j]
                j=j+1
            k=k+1

        while i < len(lefthalf):
            listToMerge[k]=lefthalf[i]
            i=i+1
            k=k+1

        while j < len(righthalf):
            listToMerge[k]=righthalf[j]
            j=j+1
            k=k+1

    # print("Merging ",listToMerge)
#End MergeSort function

#include console output / testing before writing file read functionality
bestCase = [0,1,2,3,4,5,6,7]
worstCase = [4, 0, 6, 2, 5, 1, 7, 3]
otherWorstCase = [7, 6, 5, 4, 3, 2, 1, 0]
#run mergesort function

# Start Timer and Function
start_time = time.time()
mergeSort(bestCase)
print("Base Case: %s seconds ---" % (time.time() - start_time))

# Start Timer and Function
secondd_time = time.time()
mergeSort(worstCase)
print("Worst Case: %s seconds ---" % (time.time() - secondd_time))

# Start Timer and Function
start_time = time.time()
mergeSort(otherWorstCase)
print("Other Worst Case: %s seconds ---" % (time.time() - start_time))
