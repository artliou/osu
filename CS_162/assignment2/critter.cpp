/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 9, 2016
** Description:  critter.cpp
*********************************************************************/

#include "critter.hpp"
#include <stdio.h>
#include <stdlib.h>
#include "lib_flip_display.hpp"

///////////////////////////////////////////////////////////////////////////////
//
// int Critter::GetDeathSteps() const
//
// Return this critters death counter
//
// Parameters:
//        None
//
// Return:
//        int - death counter
//

int Critter::GetDeathSteps() const
{
    return deathTurns;
}

///////////////////////////////////////////////////////////////////////////////
//
// int Critter::GetBreedSteps() const
//
// Return this critters breed counter
//
// Parameters:
//        None
//
// Return:
//        int - breed counter
//

int Critter::GetBreedSteps() const
{
    return breedTurns;
}

///////////////////////////////////////////////////////////////////////////////
//
// void Critter::SetBreedTurns (int newBreedTurns)
//
// Set this critters max turns until breed
//
// Parameters:
//        int - turns unil breed occurs
//
// Return:
//        None
//

void Critter::SetBreedTurns (int newBreedTurns)
{
    breedTurns = newBreedTurns;
}

///////////////////////////////////////////////////////////////////////////////
//
// void Critter::SetDeathTurns (int newDeathTurns)
//
// Set this critters max turns until death
//
// Parameters:
//        int - turns unil death occurs
//
// Return:
//        None
//

void Critter::SetDeathTurns (int newDeathTurns)
{
    deathTurns = newDeathTurns;
}

///////////////////////////////////////////////////////////////////////////////
//
// critterType Critter::GetCritterType() const
//
// Returns the type of this critter
//
// Parameters:
//        None
//
// Return:
//        critterType - the type of critter (ant/dodlebug)
//

critterType Critter::GetCritterType() const
{
    return critterType::CritterType__None;
}

///////////////////////////////////////////////////////////////////////////////
//
// critterMovement Critter::move()
//
// Returns the direction this critter wants to move
//
// Parameters:
//        None
//
// Return:
//        critterMovement - the direction the critter wants to move
//

critterMovement Critter::move()
{
    return (critterMovement)(rand() % (int)critterMovement::CRITTER_NUM_MOVES);
}

///////////////////////////////////////////////////////////////////////////////
//
// void Critter::eat()
//
// Increases the turn count of this critter
//
// Parameters:
//        None
//
// Return:
//        None
//

void Critter::eat()
{
    stepCounter++;
}

///////////////////////////////////////////////////////////////////////////////
//
// bool Critter::breed()
//
// Check if this critter is breeding this turn
//
// Parameters:
//        None
//
// Return:
//        boolean - true if this critter wants to breed this turn
//

bool Critter::breed()
{
    if ((stepCounter - lastBreed) >= GetBreedSteps())
    {
        lastBreed = stepCounter;
        return true;
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////////
//
// bool Critter::died()
//
// Check if this critter is dying this turn
//
// Parameters:
//        None
//
// Return:
//        boolean - true if this critter is dying this turn
//

bool Critter::died()
{
    return ((stepCounter - lastEat) >= GetDeathSteps());
}

///////////////////////////////////////////////////////////////////////////////
//
// bool Critter::GetHasMoved() const
//
// Check if this critter has already moved this turn
//
// Parameters:
//        None
//
// Return:
//        boolean - true if this critter has already moved this turn
//

bool Critter::GetHasMoved() const
{
    return hasMoved;
}

///////////////////////////////////////////////////////////////////////////////
//
// void Critter::SetHasMoved(bool moved)
//
// Set if this critter has moved this turn
//
// Parameters:
//        boolean - true if this critter has already moved this turn
//
// Return:
//        None
//

void Critter::SetHasMoved(bool moved)
{
    hasMoved = moved;
}

///////////////////////////////////////////////////////////////////////////////
//
// Critter::Critter()
//
// Critter constructor
//
// Parameters:
//        None
//
// Return:
//        None
//

Critter::Critter()
{
    stepCounter = 0;
    lastBreed = 0;
    lastEat = 0;
    hasMoved = false;
}

///////////////////////////////////////////////////////////////////////////////
//
// Critter::~Critter()
//
// Critter destructor
//
// Parameters:
//        None
//
// Return:
//        None
//

Critter::~Critter()
{

}
