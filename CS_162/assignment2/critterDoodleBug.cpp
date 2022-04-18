/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 9, 2016
** Description:  critterDoodleBug.cpp
*********************************************************************/

#include "critterDoodleBug.hpp"
#include "lib_flip_display.hpp"

///////////////////////////////////////////////////////////////////////////////
//
// critterType CritterDoodleBug::GetCritterType() const
//
// Overload to return critterType::CritterType__DoodleBug for DoodleBugs
//
// Parameters:
//        None
//
// Return:
//        critterType - Returns critterType::CritterType__DoodleBug
//

critterType CritterDoodleBug::GetCritterType() const
{
    return critterType::CritterType__DoodleBug;
}

///////////////////////////////////////////////////////////////////////////////
//
// void CritterDoodleBug::eat()
//
// Increase DoodleBug turn counter
// Reset the counter if the DoodleBug is eating an Ant
//
// Parameters:
//        None
//
// Return:
//        None
//

void CritterDoodleBug::eat()
{
    stepCounter++;
    if (eatingAnt)
    {
        eatingAnt = false;
        lastEat = stepCounter;
        debug_print (true, COLOR_CYAN, "%x was fed. Timer reset\n", this);
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// void CritterDoodleBug::EatAnt()
//
// Set the boolean to indicate that the DoodleBug is eating a Ant this turn.
//
// Parameters:
//        None
//
// Return:
//        None
//

void CritterDoodleBug::EatAnt()
{
    eatingAnt = true;
}


///////////////////////////////////////////////////////////////////////////////
//
// CritterDoodleBug::CritterDoodleBug() : Critter()
//
// CritterDoodleBug constructor
//
// Parameters:
//        None
//
// Return:
//        None
//

CritterDoodleBug::CritterDoodleBug() : Critter()
{
    eatingAnt = false;
    SetDeathTurns (CRITTER_DOODLEBUG_DEATH_STEPS);
    SetBreedTurns (CRITTER_DOODLEBUG_BREED_STEPS);
}

///////////////////////////////////////////////////////////////////////////////
//
// CritterDoodleBug::~CritterDoodleBug() : Critter()
//
// CritterDoodleBug destructor
//
// Parameters:
//        None
//
// Return:
//        None
//

CritterDoodleBug::~CritterDoodleBug()
{

}
