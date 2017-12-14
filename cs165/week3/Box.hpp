/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 10/11/17
 ** Description: Project 3.a
 ** Box.hpp

 *********************************************************************/

#ifndef Box_hpp
#define Box_hpp

#include <stdio.h>

// Defines the interface of the Box class
class Box
{
private:
  double height;
  double width;
  double length;
  double volume;
  double surfaceArea;

public:
  Box();
  Box(double height, double width, double length);

  void setHeight(double);
  double getHeight();
  void setWidth(double);
  double getWidth();
  void setLength(double);
  double getLength();

  double calcVolume();
  double calcSurfaceArea();
  //void printInfo();
};
#endif /* Box_hpp */
