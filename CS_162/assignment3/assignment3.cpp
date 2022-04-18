/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 22, 2016
** Description:  assignment3.cpp
*********************************************************************/

#include <string>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include "lib_flip_display.hpp"
#include "lib_arg_parse.hpp"
#include "assignment3.hpp"

#include "characterMedusa.hpp"
#include "characterBlueMen.hpp"
#include "characterGollum.hpp"
#include "characterReptilePeople.hpp"
#include "characterHarryPotter.hpp"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
//
// Local function definitions
//

CharacterBase * CreateCharacter(CharacterTypes type);
CharacterTypes SelectCharacter();

///////////////////////////////////////////////////////////////////////////////
//
// int main()
//
// Program entry point.
//
// Parameters:
//        int argc - number of command line parameters
//        char * argvp[] - char array of command line parameters
//
// Return:
//        int return code - zero for success
//

int main(int argc, char * argv[])
{
    // Parse command line rguments
    customArgParser::InitalizeArguments();
    argp_parse (&customArgParser::argp, argc, argv, 0, 0, &customArgParser::arguments);

    DebugConsole::debug_print (0, true, COLOR_GREEN, "Welcome to CS_162 Battle Arena (assignment 3)!!\n\n");

    if (customArgParser::arguments.debugEnable == true)
    {
      DebugConsole::SetDebugLevel (1);
    }

    // Create Characters
    CharacterBase * myCharacter = CreateCharacter (SelectCharacter());
    CharacterBase * opponent = CreateCharacter ((CharacterTypes) (rand() % CharacterTypeNumCharacters));

    unsigned int currentRound = 0;
    bool playing = true;
    while (playing)
    {
      DebugConsole::debug_print (0, true, COLOR_GREEN, "%s\tvs.\t%s\t\tRound: %d\n\n", myCharacter->GetName(), opponent->GetName(), ++currentRound);
      DebugConsole::debug_print (0, false, COLOR_WHITE, "%s Strength %d\n", myCharacter->GetName(), myCharacter->GetStrength());
      DebugConsole::debug_print (0, false, COLOR_WHITE, "%s Strength %d\n", opponent->GetName(), opponent->GetStrength());

      int myAttack = myCharacter->GenerateAttack();
      DebugConsole::debug_print (0, false, COLOR_WHITE, "%s Attacks with %d\n", myCharacter->GetName(), myAttack);
      opponent->DefendAttack (myAttack);

      int enemyAttack = opponent->GenerateAttack();
      DebugConsole::debug_print (0, false, COLOR_WHITE, "%s Attacks with %d\n", opponent->GetName(), enemyAttack);
      myCharacter->DefendAttack(enemyAttack);

      if (myCharacter->GetStrength() == 0)
      {
          DebugConsole::debug_print (0, false, COLOR_RED, "%s Died!\n", myCharacter->GetName());
          DebugConsole::debug_print (0, true, COLOR_RED, "You Lose!\n");
          break;
      }
      if (opponent->GetStrength() == 0)
      {
          DebugConsole::debug_print (0, false, COLOR_CYAN, "%s Died!\n", opponent->GetName());
          DebugConsole::debug_print (0, true, COLOR_GREEN, "You Win!\n");
          break;
      }
    }

    delete myCharacter;
    delete opponent;
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
//
// CharacterBase * CreateCharacter(CharacterTypes type)
//
// Return a pointer to a new chararcter based on the CharacterType
//
// Parameters:
//        CharcterTypes type - An enum of the type of character to create
//
// Return:
//        CharacterBase * - pointer to the new character
//

CharacterBase * CreateCharacter(CharacterTypes type)
{
  CharacterBase * newCharacter;
  switch (type)
  {
    case CharacterTypeMedusa:
      newCharacter = (CharacterBase *)new CharacterMedusa();
    break;
    case CharacterTypeGollum:
      newCharacter = (CharacterBase *)new CharacterGollum();
    break;
    case CharacterTypeReptilePeople:
      newCharacter = (CharacterBase *)new CharacterReptilePeople();
    break;
    case CharacterTypeBlueMen:
      newCharacter = (CharacterBase *)new CharacterBlueMen();
    break;
    case CharacterTypeHarryPotter:
      newCharacter = (CharacterBase *)new CharacterHarryPotter();
    break;
    default:
      newCharacter = __null;
    break;
  }
}

///////////////////////////////////////////////////////////////////////////////
//
// CharacterTypes SelectCharacter()
//
// Asks the user for the type of character to play.
//
// Parameters:
//        None
//
// Return:
//        CharcterTypes type - An enum of the type of character the user chose
//


CharacterTypes SelectCharacter()
{
  CharacterTypes characterSelect = CharacterTypeInvalid;
  while (characterSelect == -1)
  {
    char input;
    DebugConsole::debug_print (0, true, COLOR_WHITE, "Choose your character\n");
    DebugConsole::debug_print (0, true, COLOR_WHITE, "---------------------\n");
    DebugConsole::debug_print (0, true, COLOR_WHITE, "1. Medusa\n");
    DebugConsole::debug_print (0, true, COLOR_WHITE, "2. Gollum\n");
    DebugConsole::debug_print (0, true, COLOR_WHITE, "3. Reptile People\n");
    DebugConsole::debug_print (0, true, COLOR_WHITE, "4. Blue Men\n");
    DebugConsole::debug_print (0, true, COLOR_WHITE, "5. Harry Potter\n");
    if (DebugConsole::GetDebugLevel() == 0)
    {
      DebugConsole::debug_print (0, true, COLOR_WHITE, "D. Enable Debug output\n");
    }
    DebugConsole::debug_print (0, false, COLOR_WHITE, "\n\nEnter Selection: ");
    cin >> input;
    switch (input)
    {
      case 'd':
      case 'D':
        DebugConsole::SetDebugLevel(1);
        DebugConsole::debug_print (0, false, COLOR_YELLOW, "Debug output enabled!\n");
      break;
      case '1':
        characterSelect = CharacterTypeMedusa;
      break;
      case '2':
        characterSelect = CharacterTypeGollum;
      break;
      case '3':
        characterSelect = CharacterTypeReptilePeople;
      break;
      case '4':
        characterSelect = CharacterTypeBlueMen;
      break;
      case '5':
        characterSelect = CharacterTypeHarryPotter;
      break;
    }
  }
  return characterSelect;
}
