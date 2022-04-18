/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 22, 2016
** Description:  characterBase.cpp
*********************************************************************/

#include "characterBase.hpp"
#include "lib_flip_display.hpp"

///////////////////////////////////////////////////////////////////////////////
//
// unsigned int CharacterBase::GenerateAttack()
//
// Generate an attack power by rolling all the dice in
// this creatures AttackPower dice set
//
// Parameters:
//        None
//
// Return:
//        unsigned int - Generated Attack Power
//

unsigned int CharacterBase::GenerateAttack()
{
  return AttackPower.RollAllDice();
}

///////////////////////////////////////////////////////////////////////////////
//
// unsigned int CharacterBase::GenerateDefense()
//
// Generate an defense power by rolling all the dice in
// this creatures DefensePower dice set
//
// Parameters:
//        None
//
// Return:
//        unsigned int - Generated Defense Power
//

unsigned int CharacterBase::GenerateDefense()
{
  return DefensePower.RollAllDice();
}

///////////////////////////////////////////////////////////////////////////////
//
// void CharacterBase::DefendAttack(unsigned int damage)
//
// Calculate remaining strength based on attack damage from an
// opponent.
//
// Parameters:
//        unsigned int damage - Generated Defense Power
//
// Return:
//        None
//

void CharacterBase::DefendAttack(unsigned int damage)
{
  int defense = GenerateDefense();

  DebugConsole::debug_print (0, false, COLOR_CYAN, "%s took Defended %d with %d armor!\n", this->GetName(), defense, Armor);

  defense += Armor;
  // Cap defense at the incoming damage
  if (defense > damage)
  {
    defense = damage;
  }

  if ((damage - defense) >= Strength)
  {
    // Character has died...
    DebugConsole::debug_print (0, true, COLOR_RED, "%s took %d damage and died!\n", this->GetName(), (damage - defense));
    Strength = 0;
  }
  else
  {
    // Character injured, but still alive
    Strength -= (damage - defense);
    DebugConsole::debug_print (0, false, COLOR_YELLOW, "%s took %d damage!\n", this->GetName(), (damage - defense));
  }
}

///////////////////////////////////////////////////////////////////////////////
//
// unsigned int CharacterBase::GetStrength()
//
// Return this characters remaining strength.
//
// Parameters:
//        None
//
// Return:
//        unsigned int - Remaining strength
//

unsigned int CharacterBase::GetStrength()
{
  return Strength;
}
