/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 10/25/17
 ** Description: Project 4a & 4b

 *********************************************************************/
#include <iostream>
#include <string>
#include "Person.hpp"
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
std::string Person::getName() const
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
