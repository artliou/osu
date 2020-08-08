# Insert Sort for CS325 HW1
# Time: O(n^2)
# Space: O(n)
import random
import time

from math import ceil
#define stoogeSort function
# StoogeSort(A[0 ... n - 1])
def stoogesort(arr, first, last): 
    # if n = 2 and A[0] > A[1]
    # print arr, first, last
    size = last - first + 1
    if size < 2:
        # print '<1 Size'
        return arr
    elif size == 2 and arr[first] > arr[last]:
    # swap A[0] and A[1]
        # print("Swap", arr[first], arr[last])
        arr[first], arr[last] = arr[last], arr[first]
        return arr
    # else if n > 2
    elif size > 2:
        # m = ceiling(2n/3)
        m = int(ceil((2 * float(size) / 3)))
        # StoogeSort(A[0 ... m - 1])
        stoogesort(arr, first, (first + m - 1))
        # StoogeSort(A[n - m ... n - 1])
        stoogesort(arr, last - m + 1, last)
        # Stoogesort(A[0 ... m - 1])   
        stoogesort(arr, first, (first + m - 1))
        return arr

# End Function

def generateList(start, end, num): 
    result = [] 

    for i in range(num): 
        result.append(random.randint(start, end)) 

    return result

# Starter Variables
num = 5000 #n
start = 0
end = 10000

# Generate List
newList = generateList(start, end, num)
# print newList
# Start Timer and Function
end = len(newList) - 1
start_time = time.time()
stoogesort(newList, 0, end) 
print(len(newList), "--- %s seconds ---" % (time.time() - start_time))
