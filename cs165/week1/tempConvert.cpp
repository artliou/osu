
/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 9/26/17
 ** Description: Project 1.d

 1.d
 Write a program that converts Celsius temperatures to Fahrenheit temperatures.

 Please enter a Celsius temperature.
 -10.5
 The equivalent Fahrenheit temperature is:
 13.1

 Created 2 variables. Have the user input one (cTemp), which is then converted by function
 Then program reads the fTemp variable (now converted)

 *********************************************************************/

#include <iostream>
#include <string>
using namespace std;

// Project 1.d
int main()
{
    float cTemp;
    float fTemp;
    std::cout << "Please enter a Celsius temperature." << std::endl;
    std::cin >> cTemp;

    fTemp = (1.8*cTemp) + 32.0;

    std::cout << "The equivalent Fahrenheit temperature is:" <<std::endl;
    std::cout << fTemp << std::endl;

    return 0;
}
