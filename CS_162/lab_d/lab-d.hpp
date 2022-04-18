/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 9, 2016
** Description:  lab-c.hpp
*********************************************************************/

#ifndef LAB_C_H
#define LAB_C_H

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

#endif // LAB_C_H
