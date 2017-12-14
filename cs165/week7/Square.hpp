/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/8/17
 ** Description: Project 7.a

 *********************************************************************/

#ifndef Square_hpp
#define Square_hpp

#include <cmath>
#include <stdio.h>
#include "Rectangle.cpp"

class Square: public Rectangle
{
  public:
    Square(double side);

    void setWidth(double);
    void setLength(double);
};

// int main() {
//     Square sq1(10);
//     std::cout << sq1.getArea() << endl;
//     std::cout << sq1.getPerimeter() << endl;
//     return 0;
// }

#endif /* Square_hpp */
