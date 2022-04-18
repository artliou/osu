/*********************************************************************
** Author:       Jeremy Prater
** Date:         May 4, 2016
** Description:  Module 6.b assignment
*********************************************************************/

#include "LineSegment.hpp"
#include <math.h>

#ifdef Debug1
#include <iostream>
#endif

/*********************************************************************
** Description: Assignment 6.b
**
** Create a LineSegment class to describe a line
**
*********************************************************************/

/*********************************************************************
** LineSegment Function Definitions
**
*********************************************************************/

/////////////////////////////////////////////////////////////////
//
// LineSegment Constructors
//
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//
// LineSegment (Point p1, Point p2)
//
// Construct LineSegment with 2 points
//

LineSegment::LineSegment (Point p1, Point p2)
{
  this->setEnd1(p1);
  this->setEnd2(p2);
}

/////////////////////////////////////////////////////////////////
//
// LineSegment Functions
//
/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////
//
// void LineSegment::setEnd1 (Point p1)
//
// Set end point 1
//

void LineSegment::setEnd1 (Point p1)
{
  this->_p1.setXCoord(p1.getXCoord());
  this->_p1.setYCoord(p1.getYCoord());
}

/////////////////////////////////////////////////////////////////
//
// void LineSegment::setEnd2 (Point p1)
//
// Set end point 2
//

void LineSegment::setEnd2 (Point p2)
{
  this->_p2.setXCoord(p2.getXCoord());
  this->_p2.setYCoord(p2.getYCoord());
}

/////////////////////////////////////////////////////////////////
//
// Point LineSegment::getEnd1 ()
//
// Get end point 1
//

Point LineSegment::getEnd1 ()
{
  return this->_p1;
}

/////////////////////////////////////////////////////////////////
//
// Point LineSegment::getEnd2 ()
//
// Get end point 2
//

Point LineSegment::getEnd2 ()
{
  return this->_p2;
}

/////////////////////////////////////////////////////////////////
//
// Point LineSegment::length ()
//
// Get length between p1 and p2
//

double LineSegment::length ()
{
  return _p1.distanceTo(_p2);
}

/////////////////////////////////////////////////////////////////
//
// Point LineSegment::slope ()
//
// Get slope of p1 and p2
//

double LineSegment::slope()
{
  return ((double) (this->_p2.getYCoord() - this->_p1.getYCoord()) /
          (double) (this->_p2.getXCoord() - this->_p1.getXCoord()) );
}



#ifdef Debug1
int main()
{
  Point p1( 4.3 , 7.52);
  Point p2(-17.0, 1.5);
  LineSegment ls1 (p1, p2);
  double length = ls1.length();
  double slope  = ls1.slope();

  std::cout << "Length : " << length << std::endl;
  std::cout << "Slope  : " << slope  << std::endl;

  return 0;
}
#endif
