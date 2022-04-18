/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 3, 2016
** Description:  Lab B
*********************************************************************/

#include "dice.hpp"
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include "lib_flip_display.hpp"

/*********************************************************************
** Description: Lab B dice.cpp
**
** Implementation for dice.cpp
**
*********************************************************************/

/////////////////////////////////////////////////////////////////
//
// Dice::Dice()
//
// Default constructor which will create a dice with six (6) sides.
//

Dice::Dice ()
{
  this->Init(6);
}

/////////////////////////////////////////////////////////////////
//
// Dice::Dice (unsigned int numNewFaces)
//
// Overloaded constructor which will create a dice with n sides.
//

Dice::Dice (unsigned int numNewFaces)
{
  this->Init (numNewFaces);
}

/////////////////////////////////////////////////////////////////
//
// void Dice::Init (unsigned int newNumFaces)
//
// Init function for the dice class
//
// It assigns the numFaces private member and sets up the
// seed for the random number generator
//

void Dice::Init (unsigned int newNumFaces)
{
  // Use value from constructor to setup number of faces
  this->numFaces = newNumFaces;
  // Seed rand with local system time.
  unsigned int randomSeed;

  int fd = open("/dev/urandom", O_RDONLY);
  read(fd, &randomSeed, sizeof (unsigned int));
  close(fd);
  srand(randomSeed); // IRL, check for errors, close the fd, etc...
  DebugConsole::debug_print (1, false, COLOR_YELLOW, "Created Dice: Seed: %u, Faces: %u\n", randomSeed, this->numFaces);
}

/////////////////////////////////////////////////////////////////
//
// unsigned int Dice::GetNumFaces() const
//
// Return the number of faces on the dice
//

unsigned int Dice::GetNumFaces() const
{
  // Return the number of faces.
  return this->numFaces;
}

/////////////////////////////////////////////////////////////////
//
// unsigned int Dice::Roll() const
//
// Return a random number from 1 to number of faces.
//

unsigned int Dice::Roll() const
{
  // Return value from [1, GetNumFaces()]
  return 1 + (rand() % this->GetNumFaces());
}
