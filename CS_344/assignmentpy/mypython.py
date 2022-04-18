#!/bin/python

import random

outFiles = ['file1', 'file2', 'file3']

fileData = {}

def getazChar():
    return random.randint(97, 122)

for currentFile in outFiles:
    fileData[currentFile] = ""
    for data in range(0, 10):
        fileData[currentFile] += chr(getazChar())
    print ("Writing file [{}] with contents [{}]".format(currentFile, fileData[currentFile]))
    f = open(currentFile, 'w')
    f.write(fileData[currentFile])
    f.write("\n")
    f.close()

number1 = random.randint(1,42)
number2 = random.randint(1,42)
print ("Number 1: {}".format(number1))
print ("Number 2: {}".format(number2))
print ("Product: {}".format(number1 * number2))