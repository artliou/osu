# Problem 2: Bin packing optimization problem 
# Method: First Fit Decreasing algorithm.
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


def pack(values, maxValue):
    values = sorted(values, reverse=True)
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


if __name__ == '__main__':
    import random

    def packAndShow(aList, maxValue):
        print 'List with sum', sum(aList), 'requires at least', (sum(aList)+maxValue-1)/maxValue, 'bins'

        bins = pack(aList, maxValue)

        print 'Solution using', len(bins), 'bins:'
        for bin in bins:
            print bin

        print

    aList = [4, 4, 4, 6, 6, 6]
    packAndShow(aList, 10)
    bList = [20, 10, 15, 10, 5]
    packAndShow(bList, 20)
    