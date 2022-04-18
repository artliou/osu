#!/bin/python2

import os
from subprocess import call
import sys
import socket

projectName = "./cs475-project6"

def CleanBuild():
    # Delete old build
    call(["rm", "-r", "-f", "build"])
    call(["mkdir", "build"])
    os.chdir("build")


def StartBuild():
    if ("oregonstate.edu" in socket.gethostname()):
        print "=================================================================================================================================="
        print ""
        print " -- Setting up environment for GCC 5.3 on " + socket.gethostname()
        print ""
        print "=================================================================================================================================="

        os.environ["CC"]="/usr/local/common/gcc-6.3.0/bin/gcc"
        os.environ["CXX"]="/usr/local/common/gcc-6.3.0/bin/gcc"
    call(["cmake", ".."])
    call(["make"])

def RunBuild(numElements, localSize, OPMode):
    #Run a build for testing
    if (call([projectName, str(numElements), str(localSize), str(OPMode)]) != 0):
        exit(-1);

print "", sys.argv[0]
print "                    ___           ___                                  ___           ___                        ___       ___     "
print "      ___          /  /\         /  /\          ___                   /  /\         /  /\           ___        /  /\     /  /\    "
print "     /__/\        /  /::\       /  /::\        /__/\                 /  /::\       /  /:/          /__/\      /  /:/    /  /::\   "
print "     \  \:\      /  /:/\:\     /__/:/\:\       \  \:\               /  /:/\:\     /  /:/           \__\:\    /  /:/    /  /:/\:\  "
print "      \__\:\    /  /::\ \:\   _\_ \:\ \:\       \__\:\             /  /::\ \:\   /  /:/            /  /::\  /  /:/    /  /:/  \:\ "
print "      /  /::\  /__/:/\:\ \:\ /__/\ \:\ \:\      /  /::\           /__/:/\:\_\:| /__/:/     /\   __/  /:/\/ /__/:/    /__/:/ \__\:|"
print "     /  /:/\:\ \  \:\ \:\_\/ \  \:\ \:\_\/     /  /:/\:\          \  \:\ \:\/:/ \  \:\    /:/  /__/\/:/~~  \  \:\    \  \:\ /  /:/"
print "    /  /:/__\/  \  \:\ \:\    \  \:\_\:\      /  /:/__\/           \  \:\_\::/   \  \:\  /:/   \  \::/      \  \:\    \  \:\  /:/ "
print "   /__/:/        \  \:\_\/     \  \:\/:/     /__/:/                 \  \:\/:/     \  \:\/:/     \  \:\       \  \:\    \  \:\/:/  "
print "   \__\/          \  \:\        \  \::/      \__\/                   \__\::/       \  \::/       \__\/        \  \:\    \__\::/   "
print "                   \__\/         \__\/                                   ~~         \__\/                      \__\/        ~~    "
print ""
print "=================================================================================================================================="

elementsMin = 1024
elementsMax = 8 * 1024 * 1024

localWorkMin = 8
localWorkMax = 512


if (len(sys.argv) != 5):
    print "Incorrect arguments"
    print "Please specify " + sys.argv[0] + " <elements:Min> <elements:Max> <localWork:Min> <localWork:Max>"
    print " ... assuming " + sys.argv[0] + " 512 64mb 32 256"
else:
    elementsMin = int(sys.argv[1])
    elementsMax = int(sys.argv[2])
    localWorkMin = int(sys.argv[3])
    localWorkMax = int(sys.argv[4])

print "Element size Status:"
print " -- Min : " + str(elementsMin)
print " -- Max : " + str(elementsMax)
print ""

print "Local Work Status:"
print " -- Min : " + str(localWorkMin)
print " -- Max : " + str(localWorkMax)
print ""

print "=================================================================================================================================="
print " Starting Build"
print "=================================================================================================================================="

CleanBuild()
StartBuild()

print "=================================================================================================================================="
print " Executing program sequences"
print "=================================================================================================================================="

element = elementsMin
while (element <= elementsMax):
    localSize = localWorkMin
    while (localSize <= localWorkMax):
        RunBuild(element, localSize, 0) # Multiply
        RunBuild(element, localSize, 1) # Multiply-Add
        if (localSize <= 32):
            RunBuild(element, localSize, 2) # Multiply-Add w/ Reduction
        localSize *= 2
    element *= 2
