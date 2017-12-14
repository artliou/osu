/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 10/25/17
 ** Description: Project 4a & 4b

 *********************************************************************/
#ifndef Person_hpp
#define Person_hpp

#include <stdio.h>
#include <string>

class Person
{
private:
  std::string name;
  double age;

public:
  Person();
  Person(std::string, double);
  std::string getName() const;
  double getAge();
};

#endif /* Person_hpp */
