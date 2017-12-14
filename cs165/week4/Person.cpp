/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 10/18/17
 ** Description: Project 4.b
 *********************************************************************/

#include "Person.hpp"
#include <iostream>
#include <string>
using namespace std;

Person::Person()
{
    name = "Start";
    age = 5;
}

/*********************************************************************
* Description: Constructor
*********************************************************************/
Person::Person(std::string nameIn, double ageIn)
{
    name = nameIn;
    age = ageIn;
}

/*********************************************************************
* Description: Gets Name of the person
*********************************************************************/
std::string Person::getName()
{
    return name;
}

/*********************************************************************
* Description: Gets the age of the person
*********************************************************************/
double Person::getAge()
{
    return age;
}
