/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 10/18/17
 ** Description: Project 4.b

 *********************************************************************/

#ifndef Person_hpp
#define Person_hpp

#include <stdio.h>
#include <string>

// Defines the interface of the Person class
class Person
{
private:
  std::string name;
  double age;

public:
  Person();
  Person(std::string, double);
  std::string getName();
  double getAge();
};

#endif /* Person_hpp */
