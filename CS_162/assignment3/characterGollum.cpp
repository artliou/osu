/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 22, 2016
** Description:  characterGollum.cpp
*********************************************************************/

#include "characterGollum.hpp"
#include "lib_flip_display.hpp"
#include <stdlib.h>

///////////////////////////////////////////////////////////////////////////////
//
// void CharacterGollum::SetupAttackDice()
//
// Setup Gollem Attack Dice
//
// Parameters:
//        None
//
// Return:
//        None
//

void CharacterGollum::SetupAttackDice()
{
  AttackPower = DiceCombo (GOLLUM_NUM_ATTACK_DICE, GOLLUM_ATTACK_DICE_SIDES);
  JumpPower = DiceCombo (GOLLUM_NUM_JUMP_DICE, GOLLUM_JUMP_DICE_SIDES);
}

///////////////////////////////////////////////////////////////////////////////
//
//  void CharacterGollum::SetupDefenseDice()
//
// Setup Gollem Defense Dice
//
// Parameters:
//        None
//
// Return:
//        None
//

void CharacterGollum::SetupDefenseDice()
{
  DefensePower = DiceCombo (GOLLUM_NUM_DEFENSE_DICE, GOLLUM_DEFENSE_DICE_SIDES);
}

///////////////////////////////////////////////////////////////////////////////
//
// void CharacterGollum::SetupArmor()
//
// Setup Gollem Armor
//
// Parameters:
//        None
//
// Return:
//        None
//

void CharacterGollum::SetupArmor()
{
  Armor = GOLLUM_ARMOR;
}

///////////////////////////////////////////////////////////////////////////////
//
// void CharacterGollum::SetupStrength()
//
// Setup Gollem Strength
//
// Parameters:
//        None
//
// Return:
//        None
//

void CharacterGollum::SetupStrength()
{
  Strength = GOLLUM_STRENGTH;
}

///////////////////////////////////////////////////////////////////////////////
//
// const char * CharacterGollum::GetName()
//
// Return the creature name for Gollem
//
// Parameters:
//        None
//
// Return:
//        const char * - Gollem name
//

const char * CharacterGollum::GetName()
{
    return GOLLUM_NAME;
}

///////////////////////////////////////////////////////////////////////////////
//
// CharacterGollum::CharacterGollum()
//
// Class constructor for Gollem
//
// Parameters:
//        None
//
// Return:
//        None
//

CharacterGollum::CharacterGollum() : CharacterBase()
{
  DebugConsole::debug_print (1, true, COLOR_CYAN, "Creating Gollum\n");
  SetupAttackDice();
  SetupDefenseDice();
  SetupArmor();
  SetupStrength();
}

///////////////////////////////////////////////////////////////////////////////
//
// unsigned int CharacterGollum::GenerateAttack()
//
// Overloaded GenerateAttack function which has a 5% chance of
// using JumpAttack (3d6)
//
// Parameters:
//        None
//
// Return:
//        unsigned int - Gollem defense power
//

unsigned int CharacterGollum::GenerateAttack()
{
  // Generate a number between 1 - 100
  int jumpChance = (rand() % 100) + 1;
  if (jumpChance > 5)
  {
    return AttackPower.RollAllDice();
  }
  else
  {
    DebugConsole::debug_print (0, true, COLOR_MAGENTA, "Gollum used the one ring!\n");
    return JumpPower.RollAllDice();
  }
}
