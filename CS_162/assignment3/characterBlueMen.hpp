/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 22, 2016
** Description:  characterBlueMen.hpp
*********************************************************************/

#ifndef CHARACTER_BLUEMEN_HPP
#define CHARACTER_BLUEMEN_HPP

#include "characterBase.hpp"

///////////////////////////////////////////////////////////////////////////////
//
// Definitions for Blue Men stats
//


#define BLUEMEN_NUM_ATTACK_DICE    2
#define BLUEMEN_ATTACK_DICE_SIDES  10
#define BLUEMEN_NUM_DEFENSE_DICE   3
#define BLUEMEN_DEFENSE_DICE_SIDES 6

#define BLUEMEN_ARMOR              3
#define BLUEMEN_STRENGTH           12

#define BLUEMEN_NAME               "Blue Men"

///////////////////////////////////////////////////////////////////////////////
//
// class CharacterBlueMen
//
// This is the derived class for Blue Men
//
// This class provides an overloaded DefendAttack() function for
// the Blue Men ability MOB
//
// This class provides an overloaded GenerateDefense() function for
// the Blue Men ability MOB
//
// The overloaded DefenedAttack function uses a DiceCombo pointer
// which points to the current defense based on Blue Men strength
//

class CharacterBlueMen : public CharacterBase
{
private:
  DiceCombo BlueMen2DefensePower;
  DiceCombo BlueMen1DefensePower;
  DiceCombo * CurrentDefenseDice;

public:
  CharacterBlueMen();
  ~CharacterBlueMen() { }

  void SetupAttackDice();
  void SetupDefenseDice();
  void SetupArmor();
  void SetupStrength();
  const char * GetName();
  unsigned int GenerateDefense();
  void DefendAttack(unsigned int damage);
};

#endif // CHARACTER_BLUEMEN_HPP
