/*********************************************************************
** Author:       Jeremy Prater
** Date:         April 25, 2016
** Description:  Module 5.a assignment
*********************************************************************/

#include "Box.hpp"

#ifdef Debug
#include <iostream>
#endif

/*********************************************************************
** Description: Assignment 5.a
**
** Create a Box class to describe a box
**
*********************************************************************/

/*********************************************************************
** Box Function Definitions
**
*********************************************************************/

/////////////////////////////////////////////////////////////////
//
// Box Constructors
//
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//
// Box::Box()
//
// Construct Box with default size of 1.0
//

Box::Box()
{
  this->setHeight (1.0);
  this->setWidth  (1.0);
  this->setLength (1.0);
}

/////////////////////////////////////////////////////////////////
//
// Box::Box (double new_height, double new_width, double new_length)
//
// Construct Box with user defined sizes
//

Box::Box (double new_height, double new_width, double new_length)
{
  this->setHeight (new_height);
  this->setWidth  (new_width);
  this->setLength (new_length);
}

/////////////////////////////////////////////////////////////////
//
// Box Functions
//
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//
// void Box::setHeight (double new_height)
//
// Set Height of Box
//

void Box::setHeight (double new_height)
{
  this->_height = new_height;
}

/////////////////////////////////////////////////////////////////
//
// void Box::setWidth (double new_width)
//
// Set Width of Box
//

void Box::setWidth (double new_width)
{
  this->_width = new_width;
}

/////////////////////////////////////////////////////////////////
//
// void Box::setLength (double new_length)
//
// Set Length of Box
//

void Box::setLength (double new_length)
{
  this->_length = new_length;
}

/////////////////////////////////////////////////////////////////
//
// double Box::getVolume (void)
//
// Get Volume of Box by (L*W*H)
//

double Box::getVolume (void)
{
  return this->_length * this->_width * this->_height;
}

/////////////////////////////////////////////////////////////////
//
// double Box::getSurfaceArea (void)
//
// Get Surface area of Box Using
//
// SA=0
// SA += L * W * 2
// SA += H * W * 2
// SA += L * H * 2
//

double Box::getSurfaceArea (void)
{
  return (this->_length * this->_width  *2) +
         (this->_height * this->_width  *2) +
         (this->_length * this->_height *2);
}


#ifdef Debug
int main()
{
  Box * box1 = new Box();
  Box * box2 = new Box(2.4, 7.1, 5.0);

  std::cout << "Box 1 Volume: " << box1->getVolume() << std::endl;
  std::cout << "Box 1 Surface Area: " << box1->getSurfaceArea() << std::endl;

  std::cout << "Box 2 Volume: " << box2->getVolume() << std::endl;
  std::cout << "Box 2 Surface Area: " << box2->getSurfaceArea() << std::endl;

  box1->setLength (2.0);
  box1->setWidth (2.0);
  box1->setHeight (2.0);

  std::cout << "New Box 1 Volume: " << box1->getVolume() << std::endl;
  std::cout << "New Box 1 Surface Area: " << box1->getSurfaceArea() << std::endl;

  delete box1;
  delete box2;

  return 0;
}
#endif
