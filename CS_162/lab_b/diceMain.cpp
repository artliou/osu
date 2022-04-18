#include "dice.hpp"
#include "lib_flip_display.hpp"
#include <iostream>
#include <fstream>
#include <string.h>

/////////////////////////////////////////////////////////////////
//
// Function declarations
//

void GenerateFile (const char * fileName, unsigned int maxCounts, const Dice** diceArray);

/////////////////////////////////////////////////////////////////
//
// int main ()
//
// Program entry point
//

int main ()
{
  debug_print (true, COLOR_CYAN, "Dice/LoadedDice data generator V1.0\n\n");

  //Create dice array.
  Dice * diceArray[3];
  memset (diceArray, 0, sizeof (diceArray));

  // Create some dice...
  Dice dice6;
  Dice dice100(100);

  LoadedDice loaded6;
  LoadedDice loaded100(100);

  // Assign them to the dice array
  diceArray[0] = &dice6;
  diceArray[1] = &dice100;
  debug_print (true, COLOR_CYAN, "\n");

  // Generate some test files
  GenerateFile ("diceRun_10.csv", 10, (const Dice**) diceArray);
  GenerateFile ("diceRun_100.csv", 100, (const Dice**) diceArray);
  GenerateFile ("diceRun_1000.csv", 1000, (const Dice**) diceArray);

  // Assign them to the dice array
  diceArray[0] = &loaded6;
  diceArray[1] = &loaded100;

  // Generate some test files
  GenerateFile ("loadedRun_10.csv", 10, (const Dice**) diceArray);
  GenerateFile ("loadedRun_100.csv", 100, (const Dice**) diceArray);
  GenerateFile ("loadedRun_1000.csv", 1000, (const Dice**) diceArray);

  debug_print (true, COLOR_WHITE, "\n");
  return 0;
}

/////////////////////////////////////////////////////////////////
//
// void GenerateFile (const char * fileName, unsigned int maxCounts, const Dice** diceArray)
//
// GenerateFile will generate a CSV file with filename, a maxiunum number of rolls, and
// an array of dice. The internal loop will terminate when a null pointer is reached, so
// the diceArray must be null terminated, otherwise a segment violation will occur.
//

void GenerateFile (const char * fileName, unsigned int maxCounts, const Dice** diceArray)
{
  unsigned int diceIndex = 0;
  const Dice * currentDice = diceArray[diceIndex];
  debug_print (true, COLOR_WHITE, "Creating %s...\n",fileName);
  std::ofstream diceOut;
  diceOut.open (fileName);
  diceOut << "Roll, ";
  while (currentDice)
  {
    diceOut << "Dice" << currentDice->GetNumFaces() << ", ";
    currentDice = diceArray[++diceIndex];
  }
  diceOut << "Sum\n";

  for (unsigned int rollCounter = 0; rollCounter < maxCounts; rollCounter++)
  {
    unsigned int rollTotal = 0;
    diceOut << rollCounter << ", ";
    diceIndex = 0;
    currentDice = diceArray[diceIndex];
    while (currentDice)
    {
      unsigned int currentRoll = currentDice->Roll();
      rollTotal += currentRoll;
      diceOut << currentRoll  << ", ";
      currentDice = diceArray[++diceIndex];
    }
    diceOut << rollTotal << "\n";
  }
  diceOut.close();
  debug_print (true, COLOR_GREEN, "Saved %s\n\n", fileName);
}
