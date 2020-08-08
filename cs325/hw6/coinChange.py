# Question 4) Making Change

# find minimum of coins given array of coing
# m is size of coins array (number of different coins)

#n is toatal kind of coins and amount is total money to be paid
def minCoins(coins, amount):
    table = [None for x in range(amount + 1)]
    table[0] = []
    for i in range(1, amount + 1):
        for coin in coins:
            if coin > i: continue
            elif not table[i] or len(table[i - coin]) + 1 < len(table[i]):
                if table[i - coin] != None:
                    table[i] = table[i - coin][:]
                    table[i].append(coin)

    if table[-1] != None:
        print '%d coins: %s' % (len(table[-1]), table[-1])
    else:
        print 'No solution possible'

# Q4
arrA = [1, 5, 10, 25]
arrB = [1, 3, 7, 12, 27]
amountA = 202
amountB = 293
lengthA = len(arrA)
lengthB = len(arrB)

print("A: ", minCoins(arrA, amountA)) 
print("B: ", minCoins(arrB, amountB))
