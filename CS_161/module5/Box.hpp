/*********************************************************************
** Author:       Jeremy Prater
** Date:         April 25, 2016
** Description:  Module 5.a assignment
*********************************************************************/

#ifndef BOX_HPP
#define BOX_HPP

/*********************************************************************
** Description: Assignment 5.a
**
** Box header file and class declaration
**
*********************************************************************/

class Box
{
  private:

    /////////////////////////////////////////////////////////////////
    //
    // Internal Variables
    //

    double _width;
    double _height;
    double _length;

  public:

    /////////////////////////////////////////////////////////////////
    //
    // Constructors
    //

    Box (void);
    Box (double new_height, double new_width, double new_length);

    /////////////////////////////////////////////////////////////////
    //
    // Functions
    //

    void setHeight (double new_height);
    void setWidth  (double new_width);
    void setLength (double new_length);

    double getVolume      (void);
    double getSurfaceArea (void);
};

#endif // BOX_HPP
