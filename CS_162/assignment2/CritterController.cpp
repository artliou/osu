/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 9, 2016
** Description:  critterController.cpp
*********************************************************************/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "CritterController.hpp"
#include "critter.hpp"
#include "critterAnt.hpp"
#include "critterDoodleBug.hpp"
#include "lib_flip_display.hpp"

///////////////////////////////////////////////////////////////////////////////
//
// CritterController::CritterController()
//
// CritterController constructor
// Setup a default random seed.
//
// Parameters:
//        None
//
// Return:
//        None
//

CritterController::CritterController()
{
    srand(1);
}

///////////////////////////////////////////////////////////////////////////////
//
// CritterController::~CritterController()
//
// CritterController destructor
//
// Parameters:
//        None
//
// Return:
//        None
//

CritterController::~CritterController()
{
    DestroyGrid();
}

///////////////////////////////////////////////////////////////////////////////
//
// void CritterController::PrintGrid()
//
// Print the critter grid
//
// Parameters:
//        None
//
// Return:
//        None
//

void CritterController::PrintGrid()
{
    debug_print(true, COLOR_GREEN, "\nDoodleBugs and Ants V1.0\n\n");

    debug_print(false, COLOR_WHITE, "Round : %d\n\n", turnCounter);

    debug_print(true, COLOR_WHITE, "  |01234567890123456789|\n");
    debug_print(true, COLOR_WHITE, "--|--------------------|--\n");

    int dbugs = 0;
    int ants = 0;

    for(int dY=0;dY<gridY;dY++)
    {
        debug_print(true, COLOR_WHITE, "%02d|",dY);
        for (int dX = 0;dX < gridX;dX++)
        {
            if (gridMain[dX][dY] != 0)
            {
                switch (gridMain[dX][dY]->GetCritterType())
                {
                    case critterType::CritterType__None:
                        debug_print(false, COLOR_WHITE, " ");
                    break;

                    case critterType::CritterType__DoodleBug:
                        debug_print(true, COLOR_CYAN, "*");
                        dbugs++;
                    break;

                    case critterType::CritterType__Ant:
                    default:
                        debug_print(true, COLOR_RED, ".");
                        ants++;
                    break;
                }
            }
            else
            {
                debug_print(false, COLOR_WHITE, " ");
            }
        }
        debug_print(true, COLOR_WHITE, "|\n");
    }
    debug_print(true, COLOR_WHITE, "--|--------------------|--\n");
    debug_print(true, COLOR_WHITE, "  |                    |\n\n");

    debug_print(true, COLOR_WHITE,"DoodleBugs: %d\t\tAnts:%d\n",dbugs, ants);

    debug_print(true, COLOR_WHITE,"\nControls\n\n");
    debug_print(false, COLOR_WHITE,"(space) - Next Round\n");
    debug_print(false, COLOR_WHITE,"(g)     - Set the program to automatic. Use (space) to break automatic mode.\n");
    debug_print(false, COLOR_WHITE,"(q)     - Terminate Program\n\n");
    usleep (100 * 1000);
}

///////////////////////////////////////////////////////////////////////////////
//
// void CritterController::SetupLimits (int newDoodleBugBreedTurns, int newDoodleBugDeathTurns, int newAntBreedTurns, int newAntDeathTurns)
//
// Setup the death/breed turn counters for this CritterController
//
// Parameters:
//        int newDoodleBugBreedTurns - Turns until DoodleBug breeds
//        int newDoodleBugDeathTurns - Turns until DoodleBug dies
//        int newAntBreedTurns - Turns until Ant breeds
//        int newAntDeathTurns - Turns until Ant dies
//
// Return:
//        None
//

void CritterController::SetupLimits (int newDoodleBugBreedTurns, int newDoodleBugDeathTurns, int newAntBreedTurns, int newAntDeathTurns)
{
    DoodlebugBreedTurns = newDoodleBugBreedTurns;
    DoodlebugDeathTurns = newDoodleBugDeathTurns;
    AntBreedTurns = newAntBreedTurns;
    AntDeathTurns = newAntDeathTurns;

    debug_print (false, COLOR_WHITE, "DoodleBug Death Limit: ");
    debug_print (true, COLOR_CYAN, "%d\n", DoodlebugDeathTurns);
    debug_print (false, COLOR_WHITE, "DoodleBug Breed Limit: ");
    debug_print (true, COLOR_CYAN, "%d\n", DoodlebugBreedTurns);
    debug_print (false, COLOR_WHITE, "Ant Death Limit: ");
    debug_print (true, COLOR_CYAN, "%d\n", AntDeathTurns);
    debug_print (false, COLOR_WHITE, "Ant Breed Limit: ");
    debug_print (true, COLOR_CYAN, "%d\n", AntBreedTurns);
}

///////////////////////////////////////////////////////////////////////////////
//
// void CritterController::GridTurn()
//
// Preform the logic for one turn.
//
// Parameters:
//        None
//
// Return:
//        None
//

void CritterController::GridTurn()
{
    for (int dX = 0; dX < gridX;dX++)
    {
        for(int dY = 0; dY < gridY;dY++)
        {
            if ((gridMain[dX][dY] != 0) && (!gridMain[dX][dY]->GetHasMoved()))
            {
                bool validMove = false;
                int newX = dX;
                int newY = dY;
                critterMovement direction = gridMain[dX][dY]->move();

                switch (direction)
                {
                    case critterMovement::CRITTER_UP:
                    {
                        newY--;
                    }
                    break;
                    case critterMovement::CRITTER_DOWN:
                    {
                        newY++;
                    }
                    break;
                    case critterMovement::CRITTER_LEFT:
                    {
                        newX--;
                    }
                    break;
                    case critterMovement::CRITTER_RIGHT:
                    {
                        newX++;
                    }
                    break;
                }

                if ((newX >= 0) && (newX < gridX) && (newY >= 0) && (newY < gridY))
                {
                    validMove = true;
                    if (gridMain[newX][newY] != 0)
                    {
                        if ((gridMain[dX][dY]->GetCritterType() == critterType::CritterType__DoodleBug) && (gridMain[newX][newY]->GetCritterType() == critterType::CritterType__Ant))
                        {
                            // The DoodleBug will eat this ant...
                            debug_print (true, COLOR_YELLOW, "ant %x eaten...\n", gridMain[newX][newY]);
                            delete gridMain[newX][newY];
                            gridMain[newX][newY] = 0;
                            ((CritterDoodleBug*)gridMain[dX][dY])->EatAnt();
                        }
                        else if (gridMain[dX][dY]->GetCritterType() == critterType::CritterType__Ant)
                        {
                            // Ants eat everything but always die after 10 turns.
                            debug_print (true, COLOR_YELLOW, "ant %x ate %x...\n", gridMain[dX][dY] ,gridMain[newX][newY]);
                            delete gridMain[newX][newY];
                            gridMain[newX][newY] = 0;
                        }
                        else
                        {
                            validMove = false;
                        }
                    }
                }

                gridMain[dX][dY]->eat();
                if (gridMain[dX][dY]->died())
                {
                    debug_print (true, COLOR_RED, "%x died...\n", gridMain[dX][dY]);
                    delete gridMain[dX][dY];
                    gridMain[dX][dY] = 0;
                }
                else if (validMove)
                {
                    gridMain[newX][newY] = gridMain[dX][dY];
                    gridMain[newX][newY]->SetHasMoved(true);
                    if (gridMain[dX][dY]->breed())
                    {
                        debug_print (true, COLOR_CYAN, "%x breeding...\n", gridMain[dX][dY]);

                        if (gridMain[dX][dY]->GetCritterType() == critterType::CritterType__Ant)
                        {
                            gridMain[dX][dY] = new CritterAnt();
                            gridMain[dX][dY]->SetBreedTurns (AntBreedTurns);
                            gridMain[dX][dY]->SetDeathTurns (AntDeathTurns);
                        }
                        else if (gridMain[dX][dY]->GetCritterType() == critterType::CritterType__DoodleBug)
                        {
                            gridMain[dX][dY] = new CritterDoodleBug();
                            gridMain[dX][dY]->SetBreedTurns (DoodlebugBreedTurns);
                            gridMain[dX][dY]->SetDeathTurns (DoodlebugDeathTurns);
                        }
                        else
                        {
                            gridMain[dX][dY] = 0;
                        }
                    }
                    else
                    {
                        gridMain[dX][dY] = 0;
                    }
                }
            }
        }
    }
    for (int dX = 0; dX < gridX;dX++)
    {
        for(int dY = 0; dY < gridY;dY++)
        {
            if (gridMain[dX][dY] != 0)
            {
                gridMain[dX][dY]->SetHasMoved(false);
            }
        }
    }
    turnCounter++;
}

///////////////////////////////////////////////////////////////////////////////
//
// void CritterController::Randomize ()
//
// Seed the random number generator with a random value.
//
// Parameters:
//        None
//
// Return:
//        None
//

void CritterController::Randomize ()
{
    // Seed rand with local system time.
    unsigned int randomSeed;

    int fd = open("/dev/urandom", O_RDONLY);
    read(fd, &randomSeed, sizeof (unsigned int));
    close(fd);
    srand(randomSeed); // IRL, check for errors, close the fd, etc...
    debug_print (false, COLOR_YELLOW, "Using random seed : %u\n", randomSeed);
}

///////////////////////////////////////////////////////////////////////////////
//
// void CritterController::DestroyGrid()
//
// Destroy all critters in the grid.
// Called on program exit to release all memory.
//
// Parameters:
//        None
//
// Return:
//        None
//

void CritterController::DestroyGrid()
{
    for (int dX = 0; dX < gridX;dX++)
    {
        for(int dY = 0; dY < gridY;dY++)
        {
            if (gridMain[dX][dY] != 0)
            {
                delete gridMain[dX][dY];
                gridMain[dX][dY] = 0;
            }
        }
    }

}

///////////////////////////////////////////////////////////////////////////////
//
// void CritterController::SetupGrid (int numDoodleBugs, int numAnts)
//
// Destroy all critters in the grid.
// Called on program exit to release all memory.
//
// Parameters:
//        int numDoodleBugs - The number of DoodleBugs to generate
//        int numAnts - The number of Ants to generate
//
// Return:
//        None
//

void CritterController::SetupGrid (int numDoodleBugs, int numAnts)
{
    if (numAnts + numDoodleBugs > (gridX*gridY))
    {
        // Too many critters.
        // We will clip ants, then DoodleBugs.
        if (numDoodleBugs > (gridX * gridY))
        {
            numAnts = 0;
            numDoodleBugs = (gridX * gridY);
        }
        else
        {
            numAnts = (gridX * gridY) - numDoodleBugs;
        }
    }

    debug_print (false, COLOR_WHITE, "Generating grid using ");
    debug_print (true, COLOR_CYAN, "%d", numDoodleBugs);
    debug_print (false, COLOR_WHITE, " DoodleBugs and ");
    debug_print (true, COLOR_CYAN, "%d", numAnts);
    debug_print (false, COLOR_WHITE, " Ants\nUsing ");
    debug_print (true, COLOR_CYAN, "%d" ,numDoodleBugs + numAnts);
    debug_print (false, COLOR_WHITE, " of ");
    debug_print (true, COLOR_CYAN, "%d" ,(gridX*gridY));
    debug_print (false, COLOR_WHITE, " grid spaces.\n");

    for (int t=0;t<numDoodleBugs;)
    {
        int x = rand() % gridX;
        int y = rand() % gridY;
        if (gridMain[x][y] == 0)
        {
            gridMain[x][y] = new CritterDoodleBug();
            gridMain[x][y]->SetBreedTurns (DoodlebugBreedTurns);
            gridMain[x][y]->SetDeathTurns (DoodlebugDeathTurns);
            t++;
        }
    }
    for (int t=0;t<numAnts;)
    {
        int x = rand() % gridX;
        int y = rand() % gridY;
        if (gridMain[x][y] == 0)
        {
            gridMain[x][y] = new CritterAnt();
            gridMain[x][y]->SetBreedTurns (AntBreedTurns);
            gridMain[x][y]->SetDeathTurns (AntDeathTurns);
            t++;
        }
    }
}
