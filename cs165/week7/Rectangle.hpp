/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/8/17
 ** Description: Project 6.a

 *********************************************************************/

#ifndef Rectangle_hpp
#define Rectangle_hpp

#include <iostream>
#include <cmath>
#include <stdio.h>
using namespace std;

class Rectangle: public Shape {
    private:
        double width;
        double length;
    public:
        Rectangle(double width, double length);

        void setWidth(double);
        void setLength(double);

        double area();
        double perimeter();
};

// int main() {
//     Rectangle rec1(5, 6);
//     std::cout << rec1.getArea() << endl;
//     std::cout << rec1.getPerimeter() << endl;
//     return 0;
// }

#endif /* Rectangle_hpp */
