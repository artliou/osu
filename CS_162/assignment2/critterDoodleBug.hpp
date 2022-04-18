/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 9, 2016
** Description:  critterDoodleBug.hpp
*********************************************************************/

#ifndef CRITTER_DOODLEBUG_H
#define CRITTER_DOODLEBUG_H

#include "critter.hpp"

//////////////////////////////////////////////////////////////////////
//
// CritterDoodleBug derived class
//
// Based on Critter
//

class CritterDoodleBug : public Critter
{
private:
    bool eatingAnt;

public:
    critterType GetCritterType() const;
    void EatAnt();
    void eat();

    CritterDoodleBug();
    ~CritterDoodleBug();
};

#endif // CRITTER_DOODLEBUG_H
