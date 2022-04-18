/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 22, 2016
** Description:  CharacterReptilePeople.cpp
*********************************************************************/

#include "characterReptilePeople.hpp"
#include "lib_flip_display.hpp"

///////////////////////////////////////////////////////////////////////////////
//
// void CharacterReptilePeople::SetupAttackDice()
//
// Setup Reptile People Attack Dice
//
// Parameters:
//        None
//
// Return:
//        None
//

void CharacterReptilePeople::SetupAttackDice()
{
  AttackPower = DiceCombo (REPTILE_PEOPLE_NUM_ATTACK_DICE, REPTILE_PEOPLE_ATTACK_DICE_SIDES);
}

///////////////////////////////////////////////////////////////////////////////
//
//  void CharacterReptilePeople::SetupDefenseDice()
//
// Setup Reptile People Defense Dice
//
// Parameters:
//        None
//
// Return:
//        None
//

void CharacterReptilePeople::SetupDefenseDice()
{
  DefensePower = DiceCombo (REPTILE_PEOPLE_NUM_DEFENSE_DICE, REPTILE_PEOPLE_DEFENSE_DICE_SIDES);
}

///////////////////////////////////////////////////////////////////////////////
//
// void CharacterReptilePeople::SetupArmor()
//
// Setup Reptile People Armor
//
// Parameters:
//        None
//
// Return:
//        None
//

void CharacterReptilePeople::SetupArmor()
{
  Armor = REPTILE_PEOPLE_ARMOR;
}

///////////////////////////////////////////////////////////////////////////////
//
// void CharacterReptilePeople::SetupStrength()
//
// Setup Reptile People Strength
//
// Parameters:
//        None
//
// Return:
//        None
//

void CharacterReptilePeople::SetupStrength()
{
  Strength = REPTILE_PEOPLE_STRENGTH;
}

///////////////////////////////////////////////////////////////////////////////
//
// const char * CharacterReptilePeople::GetName()
//
// Return the creature name for Reptile People
//
// Parameters:
//        None
//
// Return:
//        const char * - Reptile People name
//

const char * CharacterReptilePeople::GetName()
{
    return REPTILE_PEOPLE_NAME;
}

///////////////////////////////////////////////////////////////////////////////
//
// CharacterReptilePeople::CharacterReptilePeople()
//
// Class constructor for Reptile People
//
// Parameters:
//        None
//
// Return:
//        None
//

CharacterReptilePeople::CharacterReptilePeople() : CharacterBase()
{
  DebugConsole::debug_print (1, true, COLOR_CYAN, "Creating Reptile People\n");
  SetupAttackDice();
  SetupDefenseDice();
  SetupArmor();
  SetupStrength();
}
