/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/15/17
 ** Description: Project 8.b

 *********************************************************************/

#ifndef RegularProject_hpp
#define RegularProject_hpp

#include "CustomerProject.hpp"

class RegularProject : public CustomerProject
{
  public:
    RegularProject(double hoursIn, double materialsIn, double transportationIn) : CustomerProject(hoursIn, materialsIn, transportationIn){};
    double billAmount();
};

#endif /* RegularProject_hpp */
