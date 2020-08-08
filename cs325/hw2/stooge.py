# Stooge Sort for CS325 HW2
# Time: O(n^2.709)
# Space: O(n)

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

# include console output / testing before writing file read functionality
# listtoSort = [54,26,93,17,77,31,44,55,20]
# #run sort function
# stoogeSort(listtoSort)

# Open a file caled data.txt
inFile = open("data.txt")
outFile = open("stooge.txt", "w")

# read file input
# Each line is put a string in an array
listsToSort = inFile.readlines()
print "Merging", listsToSort

# iterate through array
for line in listsToSort:
    # Clean out whitespace (\n)
    strippedLine = line.rstrip().lstrip()
    # Convert String to List of Integers
    cleanList = [int(s) for s in strippedLine.split(' ')]
    cleanList.pop(0)  # Remove First Number

    print("Raw:", cleanList)  # Check Intput
    end = len(cleanList) - 1
    stoogesort(cleanList, 0, end)  # Mergesort list
    print("Sorted:", cleanList)

    # convert list back to string
    # append string to outputFile
    string = ' '.join(map(str, cleanList))
    string.join("\n")
    print("Output String:", string)
    outFile.write((string) + "\n")
#End For Loop

inFile.close()
outFile.close()
