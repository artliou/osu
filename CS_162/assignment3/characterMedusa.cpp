/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 22, 2016
** Description:  characterMedusa.cpp
*********************************************************************/

#include "characterMedusa.hpp"
#include "lib_flip_display.hpp"

///////////////////////////////////////////////////////////////////////////////
//
// void CharacterMedusa::SetupAttackDice()
//
// Setup Medusa Attack Dice
//
// Parameters:
//        None
//
// Return:
//        None
//

void CharacterMedusa::SetupAttackDice()
{
  AttackPower = DiceCombo (MEDUSA_NUM_ATTACK_DICE, MEDUSA_ATTACK_DICE_SIDES);
}

///////////////////////////////////////////////////////////////////////////////
//
//  void CharacterMedusa::SetupDefenseDice()
//
// Setup Medusa Defense Dice
//
// Parameters:
//        None
//
// Return:
//        None
//

void CharacterMedusa::SetupDefenseDice()
{
  DefensePower = DiceCombo (MEDUSA_NUM_DEFENSE_DICE, MEDUSA_DEFENSE_DICE_SIDES);
}

///////////////////////////////////////////////////////////////////////////////
//
// void CharacterMedusa::SetupArmor()
//
// Setup Medusa Armor
//
// Parameters:
//        None
//
// Return:
//        None
//

void CharacterMedusa::SetupArmor()
{
  Armor = MEDUSA_ARMOR;
}

///////////////////////////////////////////////////////////////////////////////
//
// void CharacterMedusa::SetupStrength()
//
// Setup Medusa Strength
//
// Parameters:
//        None
//
// Return:
//        None
//

void CharacterMedusa::SetupStrength()
{
  Strength = MEDUSA_STRENGTH;
}

///////////////////////////////////////////////////////////////////////////////
//
// const char * CharacterMedusa::GetName()
//
// Return the creature name for Medusa
//
// Parameters:
//        None
//
// Return:
//        const char * - Medusa name
//

const char * CharacterMedusa::GetName()
{
    return MEDUSA_NAME;
}

///////////////////////////////////////////////////////////////////////////////
//
// CharacterMedusa::CharacterMedusa()
//
// Class constructor for Medusa
//
// Parameters:
//        None
//
// Return:
//        None
//

CharacterMedusa::CharacterMedusa() : CharacterBase()
{
  DebugConsole::debug_print (1, true, COLOR_CYAN, "Creating Medusa\n");
  SetupAttackDice();
  SetupDefenseDice();
  SetupArmor();
  SetupStrength();
}

///////////////////////////////////////////////////////////////////////////////
//
// unsigned int CharacterMedusa::GenerateAttack()
//
// Overloaded GenerateAttack function which use the GLARE ability
// if Medusa rolls a 12
//
// Parameters:
//        None
//
// Return:
//        unsigned int - Attack power
//

unsigned int CharacterMedusa::GenerateAttack()
{
  int damage = CharacterBase::GenerateAttack();
  if (damage == 12)
  {
    DebugConsole::debug_print (0, true, COLOR_MAGENTA, "Medusa used GLARE!\n");
    return 9999;
  }
  return damage;
}
