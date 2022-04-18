#!/bin/python2

import os
from subprocess import call
import sys
import socket

projectName = "./cs325-hw2"

def CleanBuild():
    # Delete old build
    call(["rm", "-r", "-f", "build"])
    call(["rm", "-r", "-f", "insert.out"])
    call(["rm", "-r", "-f", "merge.out"])
    call(["rm", "-r", "-f", "stooge.out"])
    call(["rm", "-r", "-f", "hw2.csv"])
    call(["mkdir", "build"])
    os.chdir("build")


def StartBuild():
    #if ("oregonstate.edu" in socket.gethostname()):
    #    print "=================================================================================================================================="
    #    print ""
    #    print " -- Setting up environment for GCC 6.3 on " + socket.gethostname()
    #    print ""
    #    print "=================================================================================================================================="

    #    os.environ["CC"]="/usr/local/common/gcc-6.3.0/bin/gcc"
    #    os.environ["CXX"]="/usr/local/common/gcc-6.3.0/bin/gcc"
    call(["cmake", ".."])
    call(["make"])

def RunBuild(useData, numElements):
    #Run a build for testing
    if (call([projectName, str(useData), str(numElements)]) != 0):
        exit(-1);

#########################################################################
##
## Testing start
##


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

elementsMin = 1
elementsMax = 8192

print "Element size Status:"
print " -- Min : " + str(elementsMin)
print " -- Max : " + str(elementsMax)
print ""

print "=================================================================================================================================="
print " Starting Build"
print "=================================================================================================================================="

CleanBuild()
StartBuild()

print "=================================================================================================================================="
print " Executing program sequences"
print "=================================================================================================================================="

RunBuild(1, 0) # Use data.txt

element = elementsMin
while (element <= elementsMax):
    RunBuild(0, element) # Generate data
    element *= 2
