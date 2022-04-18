#include "diceCombo.hpp"
#include "lib_flip_display.hpp"

DiceCombo::DiceCombo (unsigned int numDice, unsigned int numSides)
{
  NumDice = numDice;
  for (unsigned int currentDice = 0; currentDice < NumDice; currentDice++)
  {
    dice.push_back(Dice (numSides));
  }
}

unsigned int DiceCombo::RollAllDice()
{
  int totalRoll = 0;
  for (unsigned int currentDice = 0; currentDice < NumDice; currentDice++)
  {
    int roll = dice[currentDice].Roll();
    totalRoll += roll;
    DebugConsole::debug_print (1, false, COLOR_YELLOW, "Dice roll %d is %d. Total %d\n", currentDice, roll, totalRoll);
  }
  return totalRoll;
}
