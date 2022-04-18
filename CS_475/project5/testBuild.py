#!/bin/python

import os
from subprocess import call
import sys
import socket

projectName = "./cs475-project5"

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
    
def RunBuild(useSimd, doReduction, arraySize):
    #Run a build for testing
    call([projectName, str(useSimd), str(doReduction), str(arraySize)])

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

arraySizeMin = 1
arraySizeMax = 512 * 1024 * 1024

if (len(sys.argv) != 3):
    print "Incorrect arguments"
    print "Please specify " + sys.argv[0] + " <arraySize:Min> <arraySize:Max>"
    print " ... assuming " + sys.argv[0] + " 1  65536"
else:
    arraySizeMin = int(sys.argv[1])
    arraySizeMax = int(sys.argv[2])
    
print "Array Status:"
print " -- Min : " + str(arraySizeMin)
print " -- Max : " + str(arraySizeMax)
print ""

print "=================================================================================================================================="
print " Starting Build"
print "=================================================================================================================================="

CleanBuild()
StartBuild()

print "=================================================================================================================================="
print " Executing program sequences"
print "=================================================================================================================================="

arraySize = arraySizeMax
while (arraySize >= arraySizeMin):
    RunBuild(0, 0, arraySize)
    arraySize /= 2

arraySize = arraySizeMax
while (arraySize >= arraySizeMin):
    RunBuild(0, 1, arraySize)
    arraySize /= 2

arraySize = arraySizeMax
while (arraySize >= arraySizeMin):
    RunBuild(1, 0, arraySize)
    arraySize /= 2

arraySize = arraySizeMax
while (arraySize >= arraySizeMin):
    RunBuild(1, 1, arraySize)
    arraySize /= 2