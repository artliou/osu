/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 10/11/17
 ** Description: Project 3.a

 3) Box.cpp needs to #include Box.hpp.  When you include your own .hpp files (header files), put double quotes around them instead of angled brackets.  (You should only #include .hpp files, not .cpp files.)

 *********************************************************************/

#include <iostream>
#include <string>
#include "Box.hpp"

Box::Box()
{
    setHeight(1);
    setWidth(1);
    setLength(1);
}

Box::Box(double heightIn, double widthIn, double lengthIn)
{
    setHeight(heightIn);
    setWidth(widthIn);
    setLength(lengthIn);
}

void Box::setHeight(double heightIn)
{
    height = heightIn;
}

double Box::getHeight()
{
    return height;
}

void Box::setWidth(double widthIn)
{
    width = widthIn;
}

double Box::getWidth()
{
    return width;
}

void Box::setLength(double lengthIn)
{
    length = lengthIn;
}

double Box::getLength()
{
    return length;
}

double Box::calcVolume()
{
    volume = height * width * length;
    return volume;
}

double Box::calcSurfaceArea()
{
    double surfaceArea;
    surfaceArea = (2 * height * width) + (2 * height * length) + (2 * width * length);
    return surfaceArea;
}
