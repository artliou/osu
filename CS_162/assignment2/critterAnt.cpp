/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 9, 2016
** Description:  critterAnt.cpp
*********************************************************************/

#include "critterAnt.hpp"
#include "lib_flip_display.hpp"

///////////////////////////////////////////////////////////////////////////////
//
// critterType CritterAnt::GetCritterType() const
//
// Overload to return critterType::CritterType__Ant for Ant
//
// Parameters:
//        None
//
// Return:
//        critterType - Returns critterType::CritterType__Ant
//

critterType CritterAnt::GetCritterType() const
{
    return critterType::CritterType__Ant;
}

///////////////////////////////////////////////////////////////////////////////
//
// void CritterAnt::eat()
//
// Increase Ant turn counter
//
// Parameters:
//        None
//
// Return:
//        None
//

void CritterAnt::eat()
{
    stepCounter++;
}

///////////////////////////////////////////////////////////////////////////////
//
// CritterAnt::CritterAnt() : Critter()
//
// Ant constructor
//
// Parameters:
//        None
//
// Return:
//        None
//

CritterAnt::CritterAnt() : Critter()
{
    SetDeathTurns (CRITTER_ANT_DEATH_STEPS);
    SetBreedTurns (CRITTER_ANT_BREED_STEPS);
}

///////////////////////////////////////////////////////////////////////////////
//
// CritterAnt::~CritterAnt() : Critter()
//
// Ant destructor
//
// Parameters:
//        None
//
// Return:
//        None
//

CritterAnt::~CritterAnt()
{

}
