/*********************************************************************
** Author:       Jeremy Prater
** Date:         April 25, 2016
** Description:  Module 5.a assignment
*********************************************************************/

#ifndef POINT_HPP
#define POINT_HPP

/*********************************************************************
** Description: Assignment 5.a
**
** Box header file and class declaration
**
*********************************************************************/

class Point
{
  private:

    /////////////////////////////////////////////////////////////////
    //
    // Internal Variables
    //

    double _X;
    double _Y;

  public:

    /////////////////////////////////////////////////////////////////
    //
    // Constructors
    //

    Point();
    Point (double new_x, double new_y);

    /////////////////////////////////////////////////////////////////
    //
    // Functions
    //

    void setXCoord (double new_x);
    void setYCoord (double new_y);

    double getXCoord();
    double getYCoord();

    double distanceTo (const Point & dist_Point);
};

#endif // POINT_HPP
