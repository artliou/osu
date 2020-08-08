# Insert Sort for CS325 HW1
# Time: O(n^2)
# Space: O(n)

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

# include console output / testing before writing file read functionality
# listtoInsert = [54,26,93,17,77,31,44,55,20]
# #run mergesort function
# insertionSort(listtoInsert)


# Open a file caled data.txt
inFile = open("data.txt")
outFile = open("insertsort.txt", "w")

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
    insertionSort(cleanList)  # Mergesort list
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
