/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 9, 2016
** Description:  critterAnt.hpp
*********************************************************************/

#ifndef CRITTER_ANT_H
#define CRITTER_ANT_H

#include "critter.hpp"

//////////////////////////////////////////////////////////////////////
//
// CritterAnt derived class
//
// Based on Critter
//

class CritterAnt : public Critter
{
public:
    critterType GetCritterType() const;
    void eat();

    CritterAnt();
    ~CritterAnt();
};

#endif // CRITTER_ANT_H
