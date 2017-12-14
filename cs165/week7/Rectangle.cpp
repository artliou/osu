/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/8/17
 ** Description: Project 7.a

 Write a class called Rectangle with double fields for its length and width.
 It should have set methods for both fields.
 It should have a constructor that takes two double parameters and passes them to the set methods.
 It should also have a method called area that returns the area of the Rectangle and a method called perimeter that returns the perimeter of the Rectangle.

 *********************************************************************/

using namespace std;

#include <iostream>
#include <string>
#include "Shape.hpp"
#include "Rectangle.hpp"

Rectangle::Rectangle(double widthIn, double lengthIn)
{
    setWidth(widthIn);
    setLength(lengthIn);
}

void Rectangle::setWidth(double widthIn)
{
    width = widthIn;
}

void Rectangle::setLength(double lengthIn)
{
    length = lengthIn;
}

double Rectangle::area()
{
    return width * length;
}

double Rectangle::perimeter()
{
    return 2 * (width + length);
}
