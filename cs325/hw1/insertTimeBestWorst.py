# Insert Sort for CS325 HW1
# Time: O(n^2)
# Space: O(n)

import random
import time

#define insertsort function
def insertionSort(arr):
    # Iterate through the entire list
    for i in range(1, len(arr)):
        curr = arr[i]
        # As you go through the array, find elements that are creater than curr, then move to one position ahead of curr's position
        j = i-1
        while j >= 0 and curr < arr[j]:
                arr[j+1] = arr[j]
                j -= 1
        arr[j+1] = curr


#End Function
#include console output / testing before writing file read functionality
bestCase = [0, 1, 2, 3, 4, 5, 6, 7]
worstCase = [7, 6, 5, 4, 3, 2, 1, 0]
otherWorstCase = [4, 0, 6, 2, 5, 1, 7, 3]

#run mergesort function

# Start Timer and Function
start_time = time.time()
insertionSort(bestCase)
print("Base Case: %s seconds ---" % (time.time() - start_time))

# Start Timer and Function
secondd_time = time.time()
insertionSort(worstCase)
print("Worst Case: %s seconds ---" % (time.time() - secondd_time))


# Start Timer and Function
start_time = time.time()
insertionSort(otherWorstCase)
print("Other Worst Case: %s seconds ---" % (time.time() - start_time))
