/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 3, 2016
** Description:  Lab B
*********************************************************************/

#ifndef DICE_H
#define DICE_H

/*********************************************************************
** Description: Lab B dice.hpp
**
** Function declarations for dice.cpp and loadeddice.cpp
**
*********************************************************************/

class Dice
{
private:
  unsigned int numFaces;

  void Init (unsigned int numNewFaces);

public:
  unsigned int GetNumFaces() const;
  virtual unsigned int Roll() const;

  Dice();
  Dice (unsigned int newNumFaces);
};

class LoadedDice : public Dice
{
public:
  unsigned int Roll() const;

  LoadedDice();
  LoadedDice(unsigned int numNewFaces);
};

#endif // DICE_H
