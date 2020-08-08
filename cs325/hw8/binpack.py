# Problem 1: Bin packing optimization problem 
# Resource: https://stackoverflow.com/questions/7392143/python-implementations-of-packing-algorithm

class Bin(object):
    def __init__(self):
        self.items = []
        self.sum = 0

    def append(self, item):
        self.items.append(item)
        self.sum += item

    def __str__(self):
        return 'Bin(sum = %d, items = %s)' % (self.sum, str(self.items))

# Method: First Fit algorithm.
def pack(values, maxValue):
    bins = []

    for item in values:
        for bin in bins:
            if bin.sum + item <= maxValue:
                #print 'Adding', item, 'to', bin
                bin.append(item)
                break
        else:
            # start a new bin, if iten doesn't fit
            bin = Bin()
            bin.append(item)
            bins.append(bin)

    return bins

# Method: First Fit Decreasing algorithm. Sorting List first
def packSort(values, maxValue):
    values = sorted(values, reverse=True)
    return pack(values, maxValue)

def bestFit(values, maxValue):
    bins = []

    for item in values:
        binIndex = 0
        cap = maxValue + 1 # Least Cap 
        for index, bin in enumerate(bins, start=0):
            # print "Here", item, index, bin
            capLeft = maxValue - bin.sum
            if (capLeft >= item) and (capLeft - item <= cap):
                # print "New"
                binIndex = index
                cap = capLeft - item
        # Done with Comparison
        # See if Least Space was found
        if (cap == maxValue + 1):
            bin = Bin()
            bin.append(item)
            bins.append(bin)
        else: 
            bins[binIndex].append(item)
            # break

    return bins

# Main
if __name__ == '__main__':
    import random
    # Method: First Fit Decreasing algorithm.
    def packAndShow(aList, maxValue):
        print 'List with sum', sum(aList), 'requires at least', (sum(aList)+maxValue-1)/maxValue, 'bins'

        bins1 = pack(aList, maxValue)
        bins2 = packSort(aList, maxValue)
        bins3 = bestFit(aList, maxValue)

        print 'First Fit Solution using', len(bins1), 'bins:'
        for bin in bins1:
            print bin
        # Line Spacing
        print

        print 'First Fit Decreasing Solution using', len(bins2), 'bins:'
        for bin in bins2:
            print bin
        # Line Spacing
        print

        print 'Best Fit Solution using', len(bins3), 'bins:'
        for bin in bins3:
            print bin

        print

    def process():
        # Process Input File of bin.txt
        inFile = open("bin.txt")

        # Each line is a string in the linesToSplit array
        linesToSplit = inFile.read().splitlines()
        # print "Raw Parse", linesToSplit

        # Global Variable
        testCases = []
        while len(linesToSplit) > 0:
            testCaseNum = int(linesToSplit.pop(0))
            # print testCaseNum
            trim = testCaseNum
            while trim > 0:
                binCapacity = int(linesToSplit.pop(0))
                itemNumber = linesToSplit.pop(0) #irrelevant
                items = linesToSplit.pop(0)
                itemsArray = items.split()
                for i, item in enumerate(itemsArray, start=0):
                    itemsArray[i] = int(item)
                # print binCapacity
                # print itemsArray
                testCaseTemp = [itemsArray, binCapacity]
                testCases.append(testCaseTemp)
                trim -= 1
        # Done Parsing
        inFile.close()

        # Test Cases
        testCasesLeft = len(testCases)
        while testCasesLeft > 0:
            testCase = testCases.pop(0)
            packAndShow(testCase[0], testCase[1])
            
            testCasesLeft -= 1
        # Done

    # Comment this for the bin.py Solution
    process()
    print "BinPack Complete!"

    print "Commencing 20 Test Cases for 1c"
    # Comment out below for the 20 test cases if necessary
    print "Test Case 1"
    aList = [4, 4, 4, 6, 6, 6]
    packAndShow(aList, 10)
    print "Test Case 2"
    bList = [20, 10, 15, 10, 5]
    packAndShow(bList, 20)
    print "Test Case 3"
    cList = [2, 1, 3, 4, 5]
    packAndShow(cList, 7)
    print "Test Case 4"
    dList = [20, 10, 30, 40, 20]
    packAndShow(dList, 40)
    print "Test Case 5"
    eList = [8, 8, 1, 2, 4, 5, 15, 10, 5]
    packAndShow(eList, 17)
    print "Test Case 6"
    fList = [4, 2, 1, 1, 3]
    packAndShow(fList, 4)
    print "Test Case 7"
    gList = [29, 48, 13, 29, 58, 9, 19, 34]
    packAndShow(gList, 87)
    print "Test Case 8"
    hList = [10, 15, 10, 5, 5, 5, 5]
    packAndShow(hList, 15)
    print "Test Case 9"
    iList = [20, 30, 10, 5, 5, 40, 50, ]
    packAndShow(iList, 60)
    print "Test Case 10"
    jList = [29, 34, 72, 95, 71, 76]
    packAndShow(jList, 100)
    print "Test Case 11"
    kList = [4, 4, 9, 8, 1, 3, 2]
    packAndShow(kList, 10)
    print "Test Case 12"
    lList = [29, 28, 78, 90, 72]
    packAndShow(lList, 100)
    print "Test Case 13"
    mList = [2, 3, 5, 7, 2, 7, 8, 1, 8, 2]
    packAndShow(mList, 10)
    print "Test Case 14"
    nList = [2, 2, 4, 5 ,9, 1, 2, 4]
    packAndShow(nList, 9)
    print "Test Case 15"
    oList = [9, 20, 19, 29, 1, 30]
    packAndShow(oList, 30)
    print "Test Case 16"
    pList = [29, 20, 10, 39, 59, 1, 3, 3, 4]
    packAndShow(pList, 60)
    print "Test Case 17"
    qList = [20, 30, 40, 50, 10, 20, 30]
    packAndShow(qList, 60)
    print "Test Case 18"
    rList = [10, 2, 3, 4, 5, 6, 6, 2]
    packAndShow(rList, 10)
    print "Test Case 19"
    sList = [1, 5, 9, 5]
    packAndShow(sList, 10)
    print "Test Case 20"
    tList = [20, 5, 15, 10, 20]
    packAndShow(tList, 20)
    
    print "Completed 20 Test Cases for 1c"
# End Main
