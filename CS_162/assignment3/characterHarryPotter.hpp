/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 22, 2016
** Description:  characterHarryPotter.hpp
*********************************************************************/

#ifndef CHARACTER_HARRY_POTTER_HPP
#define CHARACTER_HARRY_POTTER_HPP

#include "characterBase.hpp"

///////////////////////////////////////////////////////////////////////////////
//
// Definitions for Harry Potter stats
//

#define HARRY_POTTER_NUM_ATTACK_DICE    2
#define HARRY_POTTER_ATTACK_DICE_SIDES  6
#define HARRY_POTTER_NUM_DEFENSE_DICE   2
#define HARRY_POTTER_DEFENSE_DICE_SIDES 6

#define HARRY_POTTER_ARMOR              0
#define HARRY_POTTER_STRENGTH           10
#define HARRY_POTTER_STRENGTH_HOGWARTS  20

#define HARRY_POTTER_NAME               "Harry Potter"

///////////////////////////////////////////////////////////////////////////////
//
// class  CharacterHarryPotter
//
// This is the derived class for Harry Potter
//
// This class provides an overloaded DefendAttack() function for
// the Harry Potter ability HOGWARTS
//

class CharacterHarryPotter : public CharacterBase
{
private:
  bool usedHogWarts;
public:
  CharacterHarryPotter();
  ~CharacterHarryPotter() { }

  void SetupAttackDice();
  void SetupDefenseDice();
  void SetupArmor();
  void SetupStrength();
  const char * GetName();

  void DefendAttack(unsigned int damage);
};

#endif // CHARACTER_HARRY_POTTER_HPP
