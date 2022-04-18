/*********************************************************************
** Author:       Jeremy Prater
** Date:         April 25, 2016
** Description:  Module 5.b assignment
*********************************************************************/

#ifndef LINESEGMENT_HPP
#define LINESEGMENT_HPP

#include "Point.hpp"

/*********************************************************************
** Description: Assignment 5.a
**
** BankAccount header file and class declaration
**
*********************************************************************/

class LineSegment
{
  private:

    /////////////////////////////////////////////////////////////////
    //
    // Internal Variables
    //
    Point _p1;
    Point _p2;

  public:

    /////////////////////////////////////////////////////////////////
    //
    // Constructors
    //

    LineSegment (Point p1, Point p2);

    /////////////////////////////////////////////////////////////////
    //
    // Functions
    //

    void setEnd1 (Point p1);
    void setEnd2 (Point p2);
    Point getEnd1 ();
    Point getEnd2 ();

    double length();
    double slope();
};

#endif // LINESEGMENT_HPP
