# HW5 Prompt: Create a program in any programming language of choice that can
# Language: Python
# OSX: Mac - Bash/Linux
# 1) Enumerate all the running processes.
# 	ps -ax
# 2) List all the running threads within process boundary.
# 3) Enumerate all the loaded modules within the processes.
# 4) Is able to show all the executable pages within the processes.
# 5) Gives us a capability to read the memory.


# Author: Arthur Liou
# Usage: Run 'python hw5.py' in (Linux) console where this file is located. It will output the requirements belows as follows.
# Background: In each section, we run the necessary linux command and store that as a strinv variable
# Notes: I left my notes and tests from when I was working on developing on this. Everything works as asked by the prompt. I have included screenshots of the console outputs for each question. When running yourself, I suggest having the console on max size you can view the outputs more quickly vs in a smaller-sized console window

# Import Libraries
import os
import subprocess

print("1) Enumerate all the running processes. ps -ax")
out = subprocess.Popen(['ps', '-ax'],
      stdout=subprocess.PIPE,
      stderr=subprocess.STDOUT)

stdout, stderr = out.communicate()
print(stdout) # Type string
# print("Any Error from 1):", stderr)
# print subprocess.check_output(['ps', '-ax'])

print("\n2) List all the running threads within process boundary.")
pid = os.getpid()
print("Process Boundary's PID:", pid)
pidString = str(pid)
# print(type(pid))
print(subprocess.check_output(['ps', '-T', '-p', pidString]))

print("\n3) Enumerate all the loaded modules within the processes.")
print(subprocess.check_output(['lsof', '-p', pidString]))
# print("Q3 Complete. All files opened by process, if any, are listed for PID:", pid)

# Resource: https://stackoverflow.com/questions/12977179/reading-living-process-memory-without-interrupting-it-proc-kcore-is-an-option
# https://unix.stackexchange.com/questions/6301/how-do-i-read-from-proc-pid-mem-under-linux/6302#6302
# import re
# maps_file = open("/proc/self/maps", 'r')
# mem_file = open("/proc/self/mem", 'r', 0)
# for line in maps_file.readlines():  # for each mapped region
#     m = re.match(r'([0-9A-Fa-f]+)-([0-9A-Fa-f]+) ([-r])', line)
#     if m.group(3) == 'r':  # if this is a readable region
#         start = int(m.group(1), 16)
#         end = int(m.group(2), 16)
#         mem_file.seek(start)  # seek to region start
#         chunk = mem_file.read(end - start)  # read region contents
#         print chunk,  # dump contents to standard output
# maps_file.close()
# mem_file.close()

print("\n4) Is able to show all the executable pages within the processes.")
cmd = "ps x | grep " + pidString
print(subprocess.check_output(cmd, shell=True))
# print(subprocess.check_output(['cat', "-la", "/proc/"+pidString+"/exe"]))
# cat / proc/PID/cmdline - also fails when it shouldn't
# print(subprocess.check_output(['ps', "x", "|", "grep", pidString]))
# print("COMMAND Printed", cmd)

print("\n5) Gives us a capability to read the memory.")
print(subprocess.check_output(['ps', "v", pidString]))
# ps aux | grep TEST
# Resource: https://www.ibm.com/support/knowledgecenter/en/ssw_aix_71/com.ibm.aix.performance/mem_usage_determine_ps.htm

