Arthur Liou

CS372 Project 2 - File Transfer Project

# How To Compile/Run Code

## INSTRUCTIONS
1) Compile ftserver.c
> gcc -o ftserver ftserver.c -lpthread

Note: ftserver.c will not compile in Flip without the -lpthread

2) Run Server / ftserver.c 
> ./ftserver [portNumber]

> EXAMPLE: ./ftserver 20020

3) Run Client / ftclient.py. Please use python3, not python

Command: -l
> python3 ftclient.py [serverHost] [portNumber] [commandFlag] [data-portNumber]

> EXAMPLE: python3 ftclient.py localhost 20020 -l 20021

Command: -g
> python3 ftclient.py [serverHost] [portNumber] [commandFlag] [data-portNumber] [transferFile]

> EXAMPLE: python3 ftclient.py localhost 20020 -g 20021 transfer.txt

4) Server will open a new port and send directory or file to client.

5) Client will display any server messages.

6) Client should exit after each command.

7) Server will wait for another connection. Server can be be stopped by sending a sigint command 
> [CTRL + C]

#### Extra Credit
- Multithreaded Server: Server will create a new thread for each new client that successfully connects.
- Authentication: On Client, Server will prompt for a username and password. The username / password is admin / pw. This is hardcoded, so any other username/password attempts will be met with a invalid username or password message.
- Attached Screenshot of Successfully Compilation, Authenticatino, multi-threading, functionality. Server run on flip1, two client running on flip2. Please see screenshot for annotation.

#### Resources:
Beej's Guide
https://docs.python.org/2/howto/sockets.html
https://docs.python.org/2/library/socket.html
https://docs.python.org/3/library/_thread.html
https://www.tutorialspoint.com/python3/python_multithreading.htm
https://www.geeksforgeeks.org/socket-programming-multi-threading-python/
https://docs.python.org/2/library/functions.html#raw_input
https://www.youtube.com/watch?v=ZwxTGGEx-1w //"How to Create a MultiThreaded Server & Allow Many Clients"
https://stackoverflow.com/questions/27127413/converting-python-string-object-to-c-char-using-ctypes //Sending Strings from Python to C & Vice-Versa
My Previous Projects from: CS372 Project 1, CS344 Sockets Projects