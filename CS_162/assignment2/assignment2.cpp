/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 9, 2016
** Description:  assignment2.cpp
*********************************************************************/

#include <stdio.h>
#include <string.h>
#include "critter.hpp"
#include "critterAnt.hpp"
#include "critterDoodleBug.hpp"
#include "CritterController.hpp"
#include "lib_flip_display.hpp"

CritterController * myController;

///////////////////////////////////////////////////////////////////////////////
//
// void printHelp()
//
// Print out the program usage help info
//
// Parameters:
//        None
//
// Return:
//        None
//

void printHelp()
{
    debug_print (true, COLOR_WHITE, "assignment 2 help :\n\n");
    debug_print (false, COLOR_WHITE, "--random | -r\t\tUse a random sequence for grid generation and movements\n");
    debug_print (false, COLOR_WHITE, "--doodledeath n\t\tOverride with n turns until a doodlebug dies.\n");
    debug_print (false, COLOR_WHITE, "--doodlebreed n\t\tOverride with n turns until a doodlebug breeds.\n");
    debug_print (false, COLOR_WHITE, "--antdeath n\t\tOverride with n turns until a ant dies.\n");
    debug_print (false, COLOR_WHITE, "--antbreed n\t\tOverride with n turns until a ant breeds.\n\n\n");
    debug_print (false, COLOR_WHITE, "example: ./assigment2 --random --doodledeath 6 --antbreed 6\n\n");
}

///////////////////////////////////////////////////////////////////////////////
//
// int main(int argc, char *argv[])
//
// Program entry point
//
// Parameters:
//        int argc - number of command line arguments
//        char *argv[] - array of char * which are the arguments
//
// Return:
//        int - result
//

int main(int argc, char *argv[])
{
    myController = new CritterController();
    debug_print (false, COLOR_WHITE, "\n\n");

    // Setup variables and defaults
    int numAnts = DEFAULT_NUM_ANTS;
    int numDoodleBugs = DEFAULT_NUM_DOODLEBUGS;

    int DoodlebugDeathTurns = CRITTER_DOODLEBUG_DEATH_STEPS;
    int DoodlebugBreedTurns = CRITTER_DOODLEBUG_BREED_STEPS;
    int AntDeathTurns = CRITTER_ANT_DEATH_STEPS;
    int AntBreedTurns = CRITTER_ANT_BREED_STEPS;

    // Parse command line parameters
    bool failure = false;
    for (int curArg = 1; ((curArg < argc) && (!failure)); curArg++)
    {
        if ((strcmp (argv[curArg], "--random")==0) || (strcmp (argv[curArg], "-r")==0))
        {
            myController->Randomize();
        }
        else if (strcmp (argv[curArg], "--doodledeath")==0)
        {
            curArg++;
            if (curArg < argc)
            {
                if (sscanf (argv[curArg], "%d", &DoodlebugDeathTurns) != 1)
                {
                    failure = true;
                }
            }
            else
            {
                failure = true;
            }
        }
        else if (strcmp (argv[curArg], "--doodlebreed")==0)
        {
            curArg++;
            if (curArg < argc)
            {
                if (sscanf (argv[curArg], "%d", &DoodlebugBreedTurns) != 1)
                {
                    failure = true;
                }
            }
            else
            {
                failure = true;
            }
        }
        else if (strcmp (argv[curArg], "--antdeath")==0)
        {
            curArg++;
            if (curArg < argc)
            {
                if (sscanf (argv[curArg], "%d", &AntDeathTurns) != 1)
                {
                    failure = true;
                }
            }
            else
            {
                failure = true;
            }
        }
        else if (strcmp (argv[curArg], "--antbreed")==0)
        {
            curArg++;
            if (curArg < argc)
            {
                if (sscanf (argv[curArg], "%d", &AntBreedTurns) != 1)
                {
                    failure = true;
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
        delete myController;
        return -1;
    }

    // Send parameters to the controller
    myController->SetupLimits (DoodlebugBreedTurns, DoodlebugDeathTurns, AntBreedTurns, AntDeathTurns);

    // Generate the critter grid
    myController->SetupGrid (numDoodleBugs, numAnts);

    // Enter main processing loop
    bool running = true;
    bool processEvent = false;
    bool autoRun = false;
    myController->PrintGrid();
    while (running)
    {
        int key = -1;
        processEvent = false;
        while (!processEvent)
        {
            key = getkey();
            switch (key)
            {
                case 'q':
                case 'Q':
                running = false;
                processEvent = true;
                break;

                case 'g':
                case 'G':
                autoRun = true;
                key=-1;
                break;

                case ' ':
                myController->GridTurn();
                processEvent = true;
                break;

                default:
                processEvent = false;
                break;
            }
            if (autoRun)
            {
                myController->GridTurn();
                processEvent = true;
                if (key != -1)
                {
                    autoRun = false;
                }
            }
        }
        myController->PrintGrid();
    }

    // Program is quitting, delete the controller to release all memory
    delete myController;
    return 0;
}
