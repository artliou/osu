/*********************************************************************
** Author:       Jeremy Prater
** Date:         April 6, 2016
** Description:  Module 2.b assignment
*********************************************************************/

#include <iostream>
#include <string>

/*********************************************************************
** Description: Assignment 2.b
**
** Convert Celsius into Fahrenheit
**
**
*********************************************************************/

/*********************************************************************
** Definitions
**
*********************************************************************/

/*********************************************************************
** double calc_fahrenheit (double celcius_temp)
**
** Convert a celcius tempature into fahrenheit
**
** Input : double (degrees in celcius)
**
** Output : double (degrees in fahrenheit)
**
*********************************************************************/

double calc_fahrenheit (double celcius_temp)
{
	return ((9.0 / 5) * celcius_temp) + 32;
}

/*********************************************************************
** int main()
**
** Program entry point
**
*********************************************************************/

int main()
{
	double celcius_temp = 0;

    std::cout << "Please enter a Celsius temperature." << std::endl;
    std::cin >> celcius_temp;
    std::cout << "The equivalent Fahrenheit temperature is:" << std::endl << calc_fahrenheit (celcius_temp) << std::endl;
    return 0;
}
