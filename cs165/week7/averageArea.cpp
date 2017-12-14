/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/8/17
 ** Description: Project 7.a

 *********************************************************************/

#include "Square.hpp"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

double averageArea(vector<Shape* > shapes)
{
    int size = shapes.size();
    double sum = 0.0;

    for (int i = 0; i < size; ++i)
    {
        sum += shapes[i]->area();
        size++;
    }
    return sum / size;
}

// int main() {
//     // double average = averageArea();
//     std::cout << "Average Area" << endl;
//     return 0;
// }