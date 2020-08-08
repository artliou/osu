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

def generateList(start, end, num): 
    result = [] 

    for i in range(num): 
        result.append(random.randint(start, end)) 

    return result

# Starter Variables
num = 10000 #n
start = 0
end = 10000

# Generate List
newList = generateList(start, end, num)
# print newList
# Start Timer and Function
start_time = time.time()
insertionSort(newList)
print(len(newList), "--- %s seconds ---" % (time.time() - start_time))
