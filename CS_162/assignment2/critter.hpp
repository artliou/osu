/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 9, 2016
** Description:  critter.hpp
*********************************************************************/

#ifndef CRITTER_H
#define CRITTER_H

//////////////////////////////////////////////////////////////////////
//
// Default values for critter breed/death
//

#define CRITTER_ANT_BREED_STEPS 3
#define CRITTER_ANT_DEATH_STEPS 10
#define CRITTER_DOODLEBUG_DEATH_STEPS 3
#define CRITTER_DOODLEBUG_BREED_STEPS 8

//////////////////////////////////////////////////////////////////////
//
// enum for types of critter
//

enum class critterType
{
    CritterType__None,
    CritterType__DoodleBug,
    CritterType__Ant
};

//////////////////////////////////////////////////////////////////////
//
// enum for types of critter movement
//

enum class critterMovement
{
    CRITTER_UP,
    CRITTER_DOWN,
    CRITTER_LEFT,
    CRITTER_RIGHT,
    CRITTER_NUM_MOVES
};


//////////////////////////////////////////////////////////////////////
//
// Critter base class
//

class Critter
{
protected:
    int stepCounter;
    int lastBreed;
    int lastEat;
    bool hasMoved;
    int breedTurns;
    int deathTurns;


public:
    void SetBreedTurns (int breedTurns);
    void SetDeathTurns (int deathTurns);

    int GetDeathSteps() const;
    int GetBreedSteps() const;
    virtual critterType GetCritterType() const;

    bool GetHasMoved() const;
    void SetHasMoved(bool moved);

    critterMovement move();
    virtual void eat();
    bool breed();
    bool died();

    Critter();
    ~Critter();
};

#endif // CRITTER_H
