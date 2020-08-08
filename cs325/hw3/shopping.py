# CS325 HW3
# Time: O(nW)
# Space: O(nW)

# inputs: items (price and weight), person (max weights)
def shoppingSpree(familyArray, weightArray, valueArray, n):
    totalPrice = 0;
    itemsArray = []
    # iterate through each element in the person array, find the best item combo, then save the items to the "local" items array"
    for capacity in familyArray:
        results = knapSack(capacity, weightArray, valueArray, n)
        totalPrice += results[0]
        itemsArray.append(results[1])
        # print "Adding Capacity", capacity, "to Current Total:", totalPrice
    # return items array: Array (length of people array) each element is an array of items

    # print "Final Total:", totalPrice
    # print "Fam", itemsArray
    # print "Print", totalPrice, itemsArray, resultsArray
    resultsArray = [totalPrice, itemsArray]
    return resultsArray
# End Algo

# Helper Function to Determine Max Value and Items Array
# W = Capacity,
def knapSack(W, weight, val, n): 
    K = [[0 for x in range(W+1)] for x in range(n+1)] 
    # Items Array
    # items = []
    for i in range(n+1): 
        for w in range(W+1): 
            if i==0 or w==0: 
                K[i][w] = 0
            elif weight[i-1] <= w: 
                K[i][w] = max(val[i-1] + K[i-1][w-weight[i-1]],  K[i-1][w]) 
                
                # print("Elif", K[i][w])
            else: 
                K[i][w] = K[i-1][w]
                # print("Else", K[i-1][w])
    # print K

    # Grab the items
    i = n
    cap = W
    items = []
    # print "Cap", cap, i, weight[i - 1]
    while i > 0 and cap > 0:
        # print type(i), type(w)
        if K[i][w] != K[i-1][w]:
            items.append(i)
            cap = cap - weight[i - 1]
            i = i - 1
        else:
            i = i - 1
    
    # print "Items", items

    return [K[n][W], items]
# End Helper Function

# Global Variables
familyArray = []
valueArray = []
weightArray = []

# Data Parsing
# # Open a file caled shopping.txt
inFile = open("shopping.txt")
outFile = open("shopping.out", "w")

# Each line is a string in the linesToSplit array
linesToSplit = inFile.read().splitlines()
# print "Arranging", linesToSplit

# Grab number of test cases
testCaseNum = int(linesToSplit.pop(0))
testCaseLoop = testCaseNum
# print "testCaseTotalNum", testCaseNum #, type(testCaseNum)

while testCaseLoop > 0:
    print "testCaseNum", testCaseLoop #, type(testCaseNum)
    # Grab Family Info
    itemNumber = int(linesToSplit.pop(0))
    # print "itemNumber:", itemNumber #, type(itemNumber)
    
    thisPriceSet = []
    thisWeightSet = []
    # parse each pair of items into price and weight
    while itemNumber > 0: 
        itemPair = linesToSplit.pop(0)
        # print itemPair, "Here" # P W
        itemArray = itemPair.split()
        # print "Item Pair:" itemPair
        # print itemArray, "Yes"
        price = int(itemArray.pop(0))
        weight = int(itemArray.pop(0))
        # print "P W", price, weight
        thisPriceSet.append(price)
        thisWeightSet.append(weight)
        itemNumber -= 1
    # print thisPriceSet, thisWeightSet
    valueArray.append(thisPriceSet)
    weightArray.append(thisWeightSet)

    # Grab Family Info
    thisFamily = []
    familyNumber = int(linesToSplit.pop(0))
    # print "FamilyNumber:", familyNumber #, type(familyNumber)
    while familyNumber > 0:
        currCapacity = int(linesToSplit.pop(0))
        thisFamily.append(currCapacity)
        familyNumber -= 1
    # End Family Loop
    # Append to Array
    familyArray.append(thisFamily)

    testCaseLoop -= 1
#End While Loop / Parsing

# Verify Information
# print "FamilyArray" familyArray
# print(familyArray), "Family Array"
# print(valueArray), "Value Array"
# print(weightArray), "Weight Array"
# n = len(valueArray)
# print len(valueArray), len(weightArray), len(familyArray)

# Proceed with Queue
queueProcess = 0
# print "Queue Processing:", queueProcess

while queueProcess < testCaseNum:
    currFam = familyArray.pop(0)
    currVal = valueArray.pop(0)
    currWeight = weightArray.pop(0)
    # Console Check
    # print currFam, currVal, currWeight
    n = len(currVal)
    results = shoppingSpree(currFam, currWeight, currVal, n)
    # print "Results Loop:", results
    maxPrice = results[0]
    familyItems = results[1]
    # print "My Test", queueProcess, "Price:", maxPrice

    # convert list back to string
    # append string to outputFile
    # string = ' '.join(map(str, cleanList))
    string = 'Test Case ' + (str(queueProcess + 1)) + "\n"
    string2 = 'Total Price ' + str(maxPrice) + "\n"
    string3 = 'Member Items:' + "\n"

    # print("Output String:", string)
    outFile.write(string + string2 + string3)
    # for loop, for each family member item, write their line
    index = 1
    for array in familyItems:
        counter = 0;
        returnString = str(index) + ": "
        # iterate through person'a items
        array.reverse() #otherwise numbers were found in reverse order
        while counter < len(array):
            #turn all their integers into a string and concat to return string
            returnString += str(array[counter]) + ' '
            # print array, str(array[counter]), "Done"
            counter += 1
        # Move onto next family member
        index += 1
        # print returnString
        outFile.write(returnString + "\n")  # New Line for Next Test Case
        # generate string onto document
        #pre for next one

    outFile.write("\n") #New Line for Next Test Case

    queueProcess += 1
# End Queue Processing

inFile.close()
outFile.close()


# Testing Functions

# Test Case 2 - Single Person Test
# val = [32, 43, 26, 50, 20, 27]
# weight = [16, 12, 4, 8, 3, 9]
# W = 25
# n = len(val)
# print(knapSack(W, weight, val, n))

# # Test Case 2 - Family Test
# familyArray = [25, 23, 21, 19]
# valueArray = [32, 43, 26, 50, 20, 27]
# weightArray = [16, 12, 4, 8, 3, 9]
# n = len(valueArray)
# shoppingSpree(familyArray, weightArray, valueArray, n)
