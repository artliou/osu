/***
* Arthur Liou
* CS344
* Program 4 - OTP - One Time Pad
***/

In this assignment, you will be creating five small programs that encrypt and decrypt information using a one-time pad-like system. I believe that you will find the topic quite fascinating: one of your challenges will be to pull yourself away from the stories of real-world espionage and tradecraft that have used the techniques you will be implementing.

These programs serve as a capstone to what you have been learning in this course, and will combine the multi-processing code you have been learning with socket-based inter-process communication. Your programs will also accessible from the command line using standard UNIX features like input/output redirection, and job control. Finally, you will write a short compilation script.

****

#Building the Program
Pseudo Code Planning
otp-enc-d & otp-dec-d are based on server.c & the two files are vertilly identical
otp-enc & otp-dec are based on client & the two files are vertilly identical

In the daemon files, my logic for implementation was to set up a while loop that kept the socket open until it was necessary to close. Using fork(), I'd create a child process that would encrypt/decrypt a file that was sent to the socket.

I had a big design choice to make. Either send the file and key separately, or combine them and send as one file. Given my analysis and background, I believe that combining would lead to better runtimes, so I went with that. I would combine the file and key into one file / the buffer and send that through. 

Thus, on the daemon's end, once I received the file. I could immediately parse it into the plain or cipher text, and the key. To know the beginning and end of the text and key, I used non alphabet/space numbers so in my daemon, I could catch whether the file was completely sent, or if complete, then I would be able to immediately split the buffer into the text and key. From there, I would apply the encryption/decryption. 

Once complete, I would send just the plaintext/ciphertext back without the key.

To make sure that the client-socket sending-receiving was correct, I found that I could alter the buffer (which I found was very convenient, as mentinoed above) to accept a encryption flag at the beggining, so during my file parsing, for reach respective daemon, I could know if the file it receives is valid for the daemon.

A big issue I ran into yesterday (Friday 8/18) was properly maintaining valid characters (there was issue with spaces and @) in the encrypted text. Everything else ran smoothly, but the encryption for it. After a bunch of hours yesterday and today, I found that I could account for those characters if I manipulated my encryption/decryption.



# Testing
Run p4gradingscript
EVERY TIME you run this script, change the port numbers you use! Otherwise, because UNIX may not let go of your ports immediately, your successive runs may fail!

# Submission
Please submit a single zip file of your program code, which may be in as many different files as you want. Inside that zip file, include the following files:

Contents
1. All of your program code

otp_enc_d: This program will run in the background as a daemon.
  Syntax: otp_enc_d listening_port

otp_enc: This program connects to otp_enc_d, and asks it to perform a one-time pad style encryption as detailed above. By itself, otp_enc doesn’t do the encryption - otp_end_d does.
  Syntax: otp_enc plaintext key port

otp_dec_d: This program performs exactly like otp_enc_d, in syntax and usage. In this case, however, otp_dec_d will decrypt ciphertext it is given, using the passed-in ciphertext and key. Thus, it returns plaintext again to otp_dec.
  Syntax: otp_enc_d listening_port (Same as otp_enc_d)

otp_dec: Similarly, this program will connect to otp_dec_d and will ask it to decrypt ciphertext using a passed-in ciphertext and key, and otherwise performs exactly like otp_enc, and must be runnable in the same three ways. otp_dec should NOT be able to connect to otp_enc_d, even if it tries to connect on the correct port - you'll need to have the programs reject each other, as described in otp_enc. 
BTW that's one long run-on sentence.
  Syntax: otp_enc plaintext key port (Same as otp_enc)

keygen: This program creates a key file of specified length. 
  Syntax: keygen keylength

2. The compilation script named "compileall"
PseudoCode & Explanation for the Compilation Script

Purpose: Compiles keygen.c
gcc -o keygen keygen.c

Purpose: Compiles otp_enc.c
gcc -o otp_enc otp_enc.c

Purpose: Compiles otp_enc_d.c
gcc -o otp_enc_d otp_enc_d.c

Purpose: Compiles otp_dec.c
gcc -o otp_dec otp_dec.c

Purpose: Compiles otp_dec_d.c
gcc -o otp_dec_d otp_dec_d.c


3. All five plaintext# files, numbered 1 through 5

4. A copy of the grading script named "p4gradingscript"

The files for contents 1-4 are in the main directory of the zipfile.
