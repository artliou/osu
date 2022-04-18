/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 22, 2016
** Description:  characterHarryPotter.cpp
*********************************************************************/

#include "characterHarryPotter.hpp"
#include "lib_flip_display.hpp"

///////////////////////////////////////////////////////////////////////////////
//
// void CharacterHarryPotter::SetupAttackDice()
//
// Setup Harry Potter Attack Dice
//
// Parameters:
//        None
//
// Return:
//        None
//

void CharacterHarryPotter::SetupAttackDice()
{
  AttackPower = DiceCombo (HARRY_POTTER_NUM_ATTACK_DICE, HARRY_POTTER_ATTACK_DICE_SIDES);
}

///////////////////////////////////////////////////////////////////////////////
//
//  void CharacterHarryPotter::SetupDefenseDice()
//
// Setup Harry Potter Defense Dice
//
// Parameters:
//        None
//
// Return:
//        None
//

void CharacterHarryPotter::SetupDefenseDice()
{
  DefensePower = DiceCombo (HARRY_POTTER_NUM_DEFENSE_DICE, HARRY_POTTER_DEFENSE_DICE_SIDES);
}

///////////////////////////////////////////////////////////////////////////////
//
// void CharacterHarryPotter::SetupArmor()
//
// Setup Harry Potter Armor
//
// Parameters:
//        None
//
// Return:
//        None
//

void CharacterHarryPotter::SetupArmor()
{
  Armor = HARRY_POTTER_ARMOR;
}

///////////////////////////////////////////////////////////////////////////////
//
// void CharacterHarryPotter::SetupStrength()
//
// Setup Harry Potter Strength
//
// Parameters:
//        None
//
// Return:
//        None
//

void CharacterHarryPotter::SetupStrength()
{
  Strength = HARRY_POTTER_STRENGTH;
  usedHogWarts = false;
}

///////////////////////////////////////////////////////////////////////////////
//
// const char * CharacterHarryPotter::GetName()
//
// Return the creature name for Harry Potter
//
// Parameters:
//        None
//
// Return:
//        const char * - Harry Potter name
//

const char * CharacterHarryPotter::GetName()
{
    return HARRY_POTTER_NAME;
}

///////////////////////////////////////////////////////////////////////////////
//
// CharacterHarryPotter::CharacterHarryPotter()
//
// Class constructor for Harry Potter
//
// Parameters:
//        None
//
// Return:
//        None
//

CharacterHarryPotter::CharacterHarryPotter() : CharacterBase()
{
  DebugConsole::debug_print (1, true, COLOR_CYAN, "Creating Harry Potter\n");
  SetupAttackDice();
  SetupDefenseDice();
  SetupArmor();
  SetupStrength();
}

///////////////////////////////////////////////////////////////////////////////
//
// unsigned int CharacterHarryPotter::DefendAttack()
//
// Overloaded DefendAttack function which has will revive Harry
// once per instance.
//
// Parameters:
//        None
//
// Return:
//        None
//

void CharacterHarryPotter::DefendAttack(unsigned int damage)
{
  CharacterBase::DefendAttack(damage);
  if ((Strength == 0) && (usedHogWarts == false))
  {
    DebugConsole::debug_print (0, true, COLOR_MAGENTA, "Harry Potter used Hogwarts!\n");
    usedHogWarts = true;
    Strength = HARRY_POTTER_STRENGTH;
  }
}
