/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 9, 2016
** Description:  lab-c.cpp
*********************************************************************/

#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <unistd.h>
#include <fcntl.h>
#include "lib_flip_display.hpp"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
//
// bool readFile (string fileName, string & outputData)
//
// Read contents of fileName into string outputData
//
// Parameters:
//        const string fileName - name of file to open
//
// Return:
//        char * - file contents or null
//

char * readFile (const char * fileName)
{
    debug_print (false, COLOR_WHITE, "\nAttempting to read: %s\n", fileName);

    int fd = open (fileName, O_RDONLY);
    if (fd < 0)
    {
        debug_print (true, COLOR_RED, "\nError reading: %s (%s)", fileName, strerror(errno));
        debug_print (true, COLOR_WHITE, "\n\n");
        return __null;
    }

    int arraySize = 50;
    int arrayLocation = 0;
    char * outputData = (char*)malloc (arraySize);
    memset (outputData, 0, arraySize);

    bool eof = false;
    while (!eof)
    {
        int sizeRead = read (fd, &outputData[arrayLocation], arraySize - arrayLocation);
        if (sizeRead == 0)
        {
            eof = true;
            break;
        }
        arrayLocation += sizeRead;
        if (arrayLocation == arraySize)
        {
            arraySize *= 2;
            outputData = (char*)realloc (outputData, arraySize);
            memset (&outputData[arrayLocation], 0, arraySize - arrayLocation);
        }
    }
    close(fd);
    return outputData;
}

///////////////////////////////////////////////////////////////////////////////
//
// bool writeFile (char * fileName, char * inputData)
//
// write contents of inputData ito fileName
//
// Parameters:
//        const string fileName - name of file to open
//        char * - file contents to write
//
// Return:
//        bool - If succeeded


bool writeFile (const char * fileName, char *inputData)
{
    debug_print (false, COLOR_WHITE, "\nAttempting to write: %s\n", fileName);
    int fd = open (fileName, O_WRONLY | O_CREAT);
    if (fd < 0)
    {
        debug_print (true, COLOR_RED, "\nError writing: %s (%s)", fileName, strerror(errno));
        debug_print (true, COLOR_WHITE, "\n\n");
        return false;
    }
    int writeLen = write (fd, inputData, strlen (inputData));
    if (writeLen != strlen (inputData))
    {
        debug_print (true, COLOR_RED, "\nError writing: %s", fileName);
        debug_print (true, COLOR_WHITE, "\n\n");
        return false;
    }
    close(fd);
    return true;
}

///////////////////////////////////////////////////////////////////////////////
//
// string recursiveReverse (string inputString)
//
// Reverse inputString.
//
// Parameters:
//        char * inputString - string to reverse
//
// Return:
//        char * - inputstring, backwards
//
// !!!! WARNING !!!! - This function does not do bounds check on the outputBuffer
//                      It can and will over write any memory
//                      Ensure outputBuffer is atleast strlen(inputString)+1 !!
//
// !!!! WARNING !!!! - This function is recursive. Please watch stack usage!!
//

char * recursiveReverse (char * inputString, char * outputBuffer)
{
    if (*inputString == 0x0)
        // The string is empty
        // This is the base case, do no call the function again.
        return outputBuffer;

    // Set the output to the recursiveReverse
    outputBuffer = recursiveReverse (&inputString[1], outputBuffer);
    outputBuffer[0] += inputString[0];

    return &outputBuffer[1];
}

///////////////////////////////////////////////////////////////////////////////
//
// void printHelp()
//
// Print command line help
//
// Parameters:
//        None
//
// Return:
//        None
//

void printHelp()
{
    debug_print (false, COLOR_WHITE, "\n\nlab-c command line usage:\n\n");
    debug_print (false, COLOR_WHITE, "--inputFile <filename>\t\tFile to read.\n");
    debug_print (false, COLOR_WHITE, "--outputFile <filename>\t\tFile to write.\n\n");
}

///////////////////////////////////////////////////////////////////////////////
//
// int main()
//
// Program entry point.
//
// Parameters:
//        int argc - number of command line parameters
//        char * argvp[] - char array of command line parameters
//
// Return:
//        int return code - zero for success
//

int main(int argc, char * argv[])
{
    string inputFilename;
    string outputFilename;

    // Parse command line parameters
    bool failure = false;
    for (int curArg = 1; ((curArg < argc) && (!failure)); curArg++)
    {
        if (strcmp (argv[curArg], "--inputFile")==0)
        {
            curArg++;
            if (curArg < argc)
            {
                inputFilename = string (argv[curArg]);
            }
            else
            {
                failure = true;
            }
        }
        else if (strcmp (argv[curArg], "--outputFile")==0)
        {
            curArg++;
            if (curArg < argc)
            {
                outputFilename = string (argv[curArg]);
            }
            else
            {
                failure = true;
            }
        }
        else
        {
            failure = true;
        }
    }

    // If the commnand line parsing failed, print the help menu and exit
    if (failure)
    {
        printHelp();
        return -1;
    }

    debug_print (true, COLOR_GREEN, "\nLAB-C : Recursive functions V1.0\n\n");

    // Prompt user if no file names were supplied from the command line
    if (inputFilename.empty())
    {
        debug_print (false, COLOR_WHITE, "Enter file to open: ");
        cin >> inputFilename;
    }
    if (outputFilename.empty())
    {
        debug_print (false, COLOR_WHITE, "Enter file to save: ");
        cin >> outputFilename;
    }

    // Load text file
    char * incomingData;
    incomingData = readFile(inputFilename.c_str());
    if (incomingData == false)
        return -1;

    // Print the contents of the text file
    debug_print (true, COLOR_CYAN, "\nInput String: \n\n");
    debug_print (true, COLOR_WHITE, "%s\n", incomingData);

    // Allocate an output buffer
    char * reverseData = (char *)malloc (strlen(incomingData) + 1);
    memset (reverseData, 0, strlen(incomingData) + 1);

    // Do the magic!
    recursiveReverse(incomingData, reverseData);

    // Print reversed output string
    debug_print (true, COLOR_CYAN, "\nReversed String: \n\n");
    debug_print (true, COLOR_WHITE, "%s\n", reverseData);

    // Save the file
    bool writeSuccess = writeFile (outputFilename.c_str(), reverseData);

    // Free the dynamic memory
    free (incomingData);
    free (reverseData);

    if (writeSuccess == false)
    {
        return -1;
    }


    debug_print (true, COLOR_GREEN, "\nProgram completed successfully!!");
    debug_print (false, COLOR_WHITE, "\n\n");

    return 0;
}
