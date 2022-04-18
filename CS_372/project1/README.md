# CS 372 Project 1
Jeremy Prater

# Execution environment
The server and client were tested and executed successfully on flip1 and flip2 servers.


# Server Instructions

ssh into flip1.engr.oregonstate.edu

cd into the extracted folder.

type

```
./chatserve.py <port num>

./chatserve.py 12500
```

# Cient Instructions

ssh into flip2.engr.oregonstate.edu

cd into extracted folder.

type

```
g++ -o chatclient chatclient.cpp
./chatclient <hostname> <port>
./chatclient flip1.engr.oregonstate.edu 12500