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

def generateList(start, end, num):
    result = []

    for i in range(num):
        result.append(random.randint(start, end))

    return result

# Starter Variables
num = 10000  # n
start = 0
end = 10000

# Generate List
newList = generateList(start, end, num)
# print newList


# Start Timer and Function
start_time = time.time()
mergeSort(newList)
print(len(newList), "--- %s seconds ---" % (time.time() - start_time))
