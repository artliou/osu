/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/8/17
 ** Description: Project 7.a

 *********************************************************************/

#ifndef Shape_hpp
#define Shape_hpp

#include <iostream>
#include <cmath>
#include <stdio.h>

using namespace std;

class Shape
{
  public:
    virtual double area() = 0; // =0 means a pure virutal
    virtual double perimeter() = 0;
};

/*
int main() {
    return 0;
}
*/
#endif /* Shape_hpp */
