/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 10/3/17
 ** Description: Project 2.d

 *********************************************************************/

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

double fallDistance(double time)
{
    double distance;
    distance = pow(time, 2) * 9.8 * 0.5; //formula condensed using 0.5 and 9.8 instead of 1/2.0 and g
    std::cout << "Object fell " << distance;
    std::cout << " meters." << std::endl;
    return distance;
}
/***
int main()
{
    double time;
    std::cout << "Enter time fallen." << std::endl;
    std::cin >> time;
    fallDistance(time);
    return 0;
}
***/
