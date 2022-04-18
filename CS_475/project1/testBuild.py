#!/bin/python

import os
from subprocess import call
import sys
projectName = "./cs475-project1"

def CleanBuild():
    # Delete old build
    call(["rm", "-r", "-f", "build"])
    call(["mkdir", "build"])
    os.chdir("build")


def StartBuild():
    call(["cmake", ".."])
    call(["make"])
    
def RunBuild(l_num_t, l_num_nodes):
    #Run a build for testing
    call([projectName, str(l_num_t), str(l_num_nodes)])

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
num_nodes_min = 64
num_nodes_max = 8192

if (len(sys.argv) != 5):
    print "Incorrect arguments"
    print "Please specify " + sys.argv[0] + " <num_t:min> <num_t:max> <num_nodes:min> <num_nodes:max>"
    print " ... assuming " + sys.argv[0] + " 1 4 64 16384"
else:
    num_t_min = int(sys.argv[1])
    num_t_max = int(sys.argv[2])
    num_nodes_min = int(sys.argv[3])
    num_nodes_max = int(sys.argv[4])
    
print "Thread Status:"
print " -- Min : " + str(num_t_min)
print " -- Max : " + str(num_t_max)
print ""
print "Node Status:"
print " -- Min : " + str(num_nodes_min)
print " -- Max : " + str(num_nodes_max)
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

thread = num_t_max
while (thread != 0):
    numnode  = num_nodes_max
    while (numnode != 0):
        RunBuild(thread, numnode)
        lastnode = int(numnode)
        numnode *= .95
        if (int(numnode) == lastnode):
            numnode = 0
    
    thread /= 2
    if (thread == 0.5):
        thread = 0
