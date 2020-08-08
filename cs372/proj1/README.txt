Arthur Liou

CS372 Project 1

# How To Compile/Run Code

## Compiling
Ensure that chatclient.c are all in the same directory
Compile by using 
> gcc -o chatClient chatclient.c -lpthread
Note: chatclient.c will not compile in Flip without the -lpthread


## Running Project

Start up Chat Server 1st, then Chat Client

Run in terminal
To Start Chat Server (program name, port number) WITHOUT ./chatserve portNum
> python chatserve.py 30020

To Start Chat Server according to grading criteria, please execute the commands below. I have included a bash script named "chatserve"
> chmod u+x chatserve
> ./chatserve 30020

To Start Chat Client: (program name, server hostname, port number)
> ./chatClient 127.0.0.1 30020

# Extra Credit: server multi-threaded, either host can make first contact, either host to send at any time without taking turns

#Testing Machine: flip1.engr.oregonstate.edu