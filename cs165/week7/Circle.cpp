/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/8/17
 ** Description: Project 7.a

 *********************************************************************/
#define _USE_MATH_DEFINES

#include <iostream>
#include <string>
#include <cmath>
#include "Circle.hpp"

Circle::Circle(double radiusIn)
{
    setRadius(radiusIn);
}

void Circle::setRadius(double radiusIn)
{
    radius = radiusIn;
}

double Circle::area()
{
    return M_PI * pow(radius, 2);
}

double Circle::perimeter()
{
    return 2 * M_PI * radius;
}
