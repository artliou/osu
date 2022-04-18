#!/bin/python2

import os
from subprocess import call
import sys
import socket

projectName = "./cs325-hw3"

def CleanBuild():
    # Delete old build
    call(["rm", "-r", "-f", "build"])
    call(["rm", "-r", "-f", "hw3.csv"])
    call(["rm", "-r", "-f", "change.txt"])
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

def RunBuild(useData, numCoins, amount):
    #Run a build for testing
    if (call([projectName, str(useData), str(numCoins), str(amount)]) != 0):
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

coinsMin = 1
coinsMax = 64 * 1024

amountMin = 1
amountMax = 64 * 1024

print "Coin Status:"
print " -- Min : " + str(coinsMin)
print " -- Max : " + str(coinsMax)
print ""
print "Amount Status:"
print " -- Min : " + str(amountMin)
print " -- Max : " + str(amountMax)
print ""

print "=================================================================================================================================="
print " Starting Build"
print "=================================================================================================================================="

CleanBuild()
StartBuild()

print "=================================================================================================================================="
print " Executing program sequences"
print "=================================================================================================================================="

RunBuild(1, 0, 0) # Use amount.txt

coins = coinsMin
amount = amountMin

while (coins <= coinsMax):
    amount = amountMin
    while(amount <= amountMax):
        RunBuild(0, coins, amount) # Generate data
        amount *= 2
    coins *= 2
