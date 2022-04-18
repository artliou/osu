/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 22, 2016
** Description:  characterBlueMen.cpp
*********************************************************************/

#include "characterBlueMen.hpp"
#include "lib_flip_display.hpp"

///////////////////////////////////////////////////////////////////////////////
//
// void CharacterBlueMen::SetupAttackDice()
//
// Setup Blue Men Attack Dice
//
// Parameters:
//        None
//
// Return:
//        None
//

void CharacterBlueMen::SetupAttackDice()
{
  AttackPower = DiceCombo (BLUEMEN_NUM_ATTACK_DICE, BLUEMEN_ATTACK_DICE_SIDES);
}

///////////////////////////////////////////////////////////////////////////////
//
//  void CharacterBlueMen::SetupDefenseDice()
//
// Setup Blue Men Defense Dice
//
// Parameters:
//        None
//
// Return:
//        None
//

void CharacterBlueMen::SetupDefenseDice()
{
  DefensePower = DiceCombo (BLUEMEN_NUM_DEFENSE_DICE, BLUEMEN_DEFENSE_DICE_SIDES);
  BlueMen2DefensePower = DiceCombo (BLUEMEN_NUM_DEFENSE_DICE - 1, BLUEMEN_DEFENSE_DICE_SIDES);
  BlueMen1DefensePower = DiceCombo (BLUEMEN_NUM_DEFENSE_DICE - 2, BLUEMEN_DEFENSE_DICE_SIDES);
  CurrentDefenseDice = &DefensePower;
}

///////////////////////////////////////////////////////////////////////////////
//
// void CharacterBlueMen::SetupArmor()
//
// Setup Blue Men Armor
//
// Parameters:
//        None
//
// Return:
//        None
//

void CharacterBlueMen::SetupArmor()
{
  Armor = BLUEMEN_ARMOR;
}

///////////////////////////////////////////////////////////////////////////////
//
// void CharacterBlueMen::SetupStrength()
//
// Setup Blue Men Strength
//
// Parameters:
//        None
//
// Return:
//        None
//

void CharacterBlueMen::SetupStrength()
{
  Strength = BLUEMEN_STRENGTH;
}

///////////////////////////////////////////////////////////////////////////////
//
// const char * CharacterBlueMen::GetName()
//
// Return the creature name for Blue Men
//
// Parameters:
//        None
//
// Return:
//        const char * - Blue Men name
//

const char * CharacterBlueMen::GetName()
{
    return BLUEMEN_NAME;
}

///////////////////////////////////////////////////////////////////////////////
//
// CharacterBlueMen::CharacterBlueMen()
//
// Class constructor for Blue Men
//
// Parameters:
//        None
//
// Return:
//        None
//

CharacterBlueMen::CharacterBlueMen() : CharacterBase()
{
  DebugConsole::debug_print (1, true, COLOR_CYAN, "Creating BlueMen\n");
  SetupAttackDice();
  SetupDefenseDice();
  SetupArmor();
  SetupStrength();
}

///////////////////////////////////////////////////////////////////////////////
//
// unsigned int CharacterBlueMen::GenerateDefense()
//
// Overloaded GenerateDefense function which uses the CurrentDefenseDice
// pointer to roll dice.
//
// Strength > 8 - 3d6
// Strength > 4 - 2d6
// Strength <= 4 - 1d6
//
// Parameters:
//        None
//
// Return:
//        unsigned int - Blue Men defense power
//

unsigned int CharacterBlueMen::GenerateDefense()
{
  return CurrentDefenseDice->RollAllDice();
}

///////////////////////////////////////////////////////////////////////////////
//
// void CharacterBlueMen::DefendAttack(unsigned int damage)
//
// Overloaded Defend Attack function which uses sets CurrentDefenseDice
// based on remaining strength.
//
// Strength > 8 - 3d6
// Strength > 4 - 2d6
// Strength <= 4 - 1d6
//
// Parameters:
//        None
//
// Return:
//        None
//

void CharacterBlueMen::DefendAttack(unsigned int damage)
{
  CharacterBase::DefendAttack(damage);
  if (Strength == 0)
  {
    // Blue men already died.
    return;
  }
  else if ((Strength <= 4) && (CurrentDefenseDice != &BlueMen1DefensePower))
  {
    CurrentDefenseDice = &BlueMen1DefensePower;
    DebugConsole::debug_print (0, true, COLOR_MAGENTA, "Blue man died. 1 Blueman remains. Defense Power is 1d6!\n");
  }
  else if ((Strength <= 8) && (CurrentDefenseDice != &BlueMen2DefensePower))
  {
    CurrentDefenseDice = &BlueMen2DefensePower;
    DebugConsole::debug_print (0, true, COLOR_MAGENTA, "Blue man died. 2 Blueman remains. Defense Power is 2d6!\n");
  }
}
