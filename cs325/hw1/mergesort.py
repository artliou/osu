# Merge Sort for CS325 HW1
# Time: O(nlogn)
# Space: O(n)

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

# include console output / testing before writing file read functionality
# listToMerge = [54,26,93,17,77,31,44,55,20]
# #run mergesort function
# mergeSort(listToMerge)

# Open a file caled data.txt
inFile = open("data.txt")
outFile = open("mergesort.txt", "w")

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
    length = cleanList.pop(0)  # Remove First Number
    
    print "Raw:", cleanList  # Check Intput
    mergeSort(cleanList)  # Mergesort list
    print "Sorted:", cleanList

    # convert list back to string
    # append string to outputFile
    string = ' '.join(map(str, cleanList))
    string.join("\n")
    print "Output String:", string
    outFile.write((string) + "\n")

    #Time Complexity
    print length

#End For Loop

inFile.close()
outFile.close()


