#!/bin/python

import os
from subprocess import call
import sys
import socket

projectName = "./cs475-project2"

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
    
def RunBuild(l_num_t, l_mode, l_chunk):
    #Run a build for testing
    call([projectName, str(l_num_t), l_mode, str(l_chunk)])

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

num_t_min = 1
num_t_max = 16
modes = ["static", "dynamic"]
chunksizes = [1, 4096]
thread = num_t_max

if (len(sys.argv) != 3):
    print "Incorrect arguments"
    print "Please specify " + sys.argv[0] + " <num_t:min> <num_t:max>"
    print " ... assuming " + sys.argv[0] + " 1 64"
else:
    num_t_min = int(sys.argv[1])
    num_t_max = int(sys.argv[2])
    
print "Thread Status:"
print " -- Min : " + str(num_t_min)
print " -- Max : " + str(num_t_max)
print ""
print "Modes Status:"
for mode in modes:
    print " -- Mode : " + mode
print ""
print "ChunkSizes:"
for chunk in chunksizes:
    print " -- ChunkSize : " + str(chunk)
print ""
print ""

print "=================================================================================================================================="
print " Starting Build"
print "=================================================================================================================================="

CleanBuild()
StartBuild()

print "=================================================================================================================================="
print " Executing program sequences"
print "=================================================================================================================================="

for mode in modes:
    for chunk in chunksizes:
        thread = num_t_max
        while (thread != 0):
            RunBuild(thread, mode, chunk)
            if (thread > 128):
                thread -= 4
            elif (thread > 2):
                thread -= 2
            else:
                thread -= 1
