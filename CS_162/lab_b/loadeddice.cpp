#include "dice.hpp"
#include <stdlib.h>

/////////////////////////////////////////////////////////////////
//
// LoadedDice::LoadedDice() : Dice()
//
// Default constructor which will create a loaded dice with six (6) sides.
//


LoadedDice::LoadedDice() : Dice()
{

}

/////////////////////////////////////////////////////////////////
//
// LoadedDice::LoadedDice(unsigned int newNumFaces) : Dice(newNumFaces)
//
// Overloaded constructor which will create a loaded dice with n sides.
//

LoadedDice::LoadedDice(unsigned int newNumFaces) : Dice(newNumFaces)
{

}

/////////////////////////////////////////////////////////////////
//
// unsigned int LoadedDice::Roll() const
//
// Return a random number from 1 to number of faces.
//
// The function has a 5% chance of being loaded (+1)
//

unsigned int LoadedDice::Roll() const
{
  // Get value
  int result = Dice::Roll();
  // Check for 5 percent chance to be LoadedDice.
  if ((rand() % 100) >= 5)
  {
    // Increase result.
    result++;
    // Check if we are over max faces.
    if (result > this->GetNumFaces())
    {
      //Set result to max faces
      result = this->GetNumFaces();
    }
  }
  // Return result.
  return result;
}
