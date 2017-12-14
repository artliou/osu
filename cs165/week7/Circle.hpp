/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/8/17
 ** Description: Project 7.a

 *********************************************************************/

#ifndef Circle_hpp
#define Circle_hpp

#include <iostream>
#include "Shape.hpp"

using namespace std;

class Circle: public Shape {
    private:
        double radius;
    public:
        Circle(double radiusIn);

        void setRadius(double);

        double area();
        double perimeter();
};

// int main() {
//     Circle cir1(5);
//     std::cout << cir1.getArea() << endl;
//     std::cout << cir1.getPerimeter() << endl;
//     return 0;
// }

#endif /* Circle_hpp */
