#!/bin/python

import random

outFiles = ['file1', 'file2', 'file3']
fileData = {}

def randomizeChar():
    return random.randint(97, 122)

for currFile in outFiles:
    fileData[currFile] = ""
    for data in range(0, 10):
        fileData[currFile] += chr(randomizeChar())
    print(fileData[currFile])
    f = open(currFile, 'w')
    f.write(fileData[currFile])
    f.write("\n")
    f.close()

number1 = random.randint(1,42)
number2 = random.randint(1,42)
print(number1)
print(number2)
print(number1 * number2)