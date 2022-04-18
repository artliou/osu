/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 15, 2016
** Description:  lab-d.cpp
*********************************************************************/

#include <string>
#include <fstream>
#include <cstring>
#include <iostream>
#include <limits>
#include "lib_flip_display.hpp"
#include "transformer.hpp"

using namespace std;

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
    debug_print (false, COLOR_WHITE, "\n\nlab-d command line usage:\n\n");
    debug_print (false, COLOR_WHITE, "--inputFile <filename>\t\tFile to read.\n");
    debug_print (false, COLOR_WHITE, "--encryptionKey <int>\t\tEncryption Key to use.\n\n");
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
    string outputCopy;
    string outputToUpper;
    string outputEncryption;
    string outputOrdered;
    int encryptionKey;
    bool usingKey = false;

    //////////////////////////////////////////////////////////////////
    //
    // Parse command line parameters
    //
    // This will be replaced with argp_parse in future labs...
    //

    bool failure = false;
    for (int curArg = 1; ((curArg < argc) && (!failure)); curArg++)
    {
        if (strcmp (argv[curArg], "--inputFile")==0)
        {
            curArg++;
            if ((curArg < argc) && (argv[curArg] != __null))
            {
                inputFilename = string (argv[curArg]);
            }
            else
            {
                failure = true;
            }
        }
        else if (strcmp (argv[curArg], "--encryptionKey")==0)
        {
            curArg++;
            if ((curArg < argc) && (argv[curArg] != __null))
            {
                if (sscanf (argv[curArg], "%d", &encryptionKey) != 1)
                {
                    failure = true;
                }
                else
                {
                    usingKey = true;
                }
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

    if (inputFilename.empty())
    {
        debug_print (true, COLOR_WHITE, "Enter input filename:");
        debug_print (false, COLOR_WHITE, " ");
        std:cin >> inputFilename;
    }

    if (!usingKey)
    {
        debug_print (true, COLOR_WHITE, "Enter Encryption Key:");
        debug_print (false, COLOR_WHITE, " ");
        while(!(cin >> encryptionKey))
        {
            debug_print (true, COLOR_YELLOW, "\nInvalid integer...");
            debug_print (false, COLOR_WHITE, "\n\n");
            debug_print (true, COLOR_WHITE, "Enter Encryption Key:");
            debug_print (false, COLOR_WHITE, " ");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        usingKey = true;
    }

    outputCopy = inputFilename + ".outputCopy";
    outputToUpper = inputFilename + ".outputToUpper";
    outputEncryption = inputFilename + ".outputEncryption";
    outputOrdered = inputFilename + ".outputOrdered";

    debug_print (false, COLOR_CYAN, "\n");
    debug_print (false, COLOR_CYAN, "Input file: ");
    debug_print (false, COLOR_WHITE, "%s\n", inputFilename.c_str());

    debug_print (false, COLOR_CYAN, "Copy Output file: ");
    debug_print (false, COLOR_WHITE, "%s\n", outputCopy.c_str());

    debug_print (false, COLOR_CYAN, "Encryption output file: ");
    debug_print (false, COLOR_WHITE, "%s\n", outputEncryption.c_str());
    debug_print (false, COLOR_CYAN, "Encryption Key: ");
    debug_print (false, COLOR_WHITE, "%d\n", encryptionKey);

    debug_print (false, COLOR_CYAN, "ToUpper output file: ");
    debug_print (false, COLOR_WHITE, "%s\n", outputToUpper.c_str());

    debug_print (false, COLOR_CYAN, "OrderedOutput file: ");
    debug_print (false, COLOR_WHITE, "%s\n", outputOrdered.c_str());
    debug_print (false, COLOR_WHITE, "\n");

    std::ifstream inputStream (inputFilename.c_str());

    if (!inputStream.good())
    {
        debug_print (true, COLOR_RED, "Input file %s not found!", inputFilename.c_str());
        debug_print (false, COLOR_WHITE, "\n\n");
        return -1;
    }

    std::ofstream outputCopyStream (outputCopy.c_str());
    std::ofstream outputToUpperStream (outputToUpper.c_str());
    std::ofstream outputEncryptionStream (outputEncryption.c_str());
    std::ofstream outputOrderdedStream (outputOrdered.c_str());

    Copy transformCopy;
    ToUpper transformToUpper;
    Encryption transformEncryption(encryptionKey);
    OrderedOutput transformOrderedOutput;

    transformCopy.doFilter (inputStream, outputCopyStream);
    transformToUpper.doFilter (inputStream, outputToUpperStream);
    transformEncryption.doFilter (inputStream, outputEncryptionStream);
    transformOrderedOutput.doFilter (inputStream, outputOrderdedStream);

    outputCopyStream.close();
    outputToUpperStream.close();
    outputEncryptionStream.close();
    outputOrderdedStream.close();
    inputStream.close();

    return 0;
}
