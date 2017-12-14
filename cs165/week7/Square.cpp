/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/8/17
 ** Description: Project 7.a

 *********************************************************************/

#include "Square.hpp"
#include <iostream>
#include <string>

Square::Square(double side): Rectangle(side, side) {}

void Square::setLength(double side)
{
    Rectangle::setWidth(side);
    Rectangle::setLength(side);
}

void Square::setWidth(double side)
{
    Rectangle::setWidth(side);
    Rectangle::setLength(side);
}
