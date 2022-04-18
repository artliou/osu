/*********************************************************************
** Author:       Jeremy Prater
** Date:         May 3, 2016
** Description:  Module 6.a assignment
*********************************************************************/

#include "Point.hpp"
#include <math.h>

#ifdef Debug
#include <iostream>
#endif

/*********************************************************************
** Description: Assignment 6.a
**
** Create a Point class to describe a point
**
*********************************************************************/

/*********************************************************************
** Point Function Definitions
**
*********************************************************************/

/////////////////////////////////////////////////////////////////
//
// Point Constructors
//
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//
// Point::Point()
//
// Construct Point with default coordinates (0,0)
//

Point::Point()
{
  this->setXCoord (0.0);
  this->setYCoord (0.0);
}

/////////////////////////////////////////////////////////////////
//
// Point::Point (double new_x, double new_y)
//
// Construct Point with user defined location
//

Point::Point (double new_x, double new_y)
{
  this->setXCoord (new_x);
  this->setYCoord (new_y);
}

/////////////////////////////////////////////////////////////////
//
// Point Functions
//
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//
// void Point::setXCoord (double new_x)
//
// Set X member of Point
//

void Point::setXCoord (double new_x)
{
  this->_X = new_x;
}

/////////////////////////////////////////////////////////////////
//
// void Point::setYCoord (double new_y)
//
// Set Y member of Point
//

void Point::setYCoord (double new_y)
{
  this->_Y = new_y;
}

/////////////////////////////////////////////////////////////////
//
// double Point::getYCoord ()
//
// Get X member of Point
//
double Point::getXCoord() { return _X; }

/////////////////////////////////////////////////////////////////
//
// double Point::getYCoord ()
//
// Get Y member of Point
//
double Point::getYCoord() { return _Y; }


/////////////////////////////////////////////////////////////////
//
// double distanceTo (Point &dist_Point)
//
// Return distance to another point
//
double Point::distanceTo (const Point & dist_Point)
{
  return sqrt (pow(((Point)dist_Point).getXCoord() - this->_X, 2) +
               pow(((Point)dist_Point).getYCoord() - this->_Y, 2) );
}

#ifdef Debug
int main()
{
  Point p1(-1.5, 0.0);
  Point p2( 1.5, 4.0);

  double dist = p1.distanceTo(p2);

  std::cout << "Distance : " << dist << std::endl;

  return 0;
}
#endif
