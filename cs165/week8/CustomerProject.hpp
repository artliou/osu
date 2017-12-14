/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/15/17
 ** Description: Project 8.b

 *********************************************************************/

#ifndef CustomerProject_hpp
#define CustomerProject_hpp

#include <iostream>
#include <cmath>

using namespace std;

class CustomerProject
{
  protected:
    double hours, materials, transportation;

  public:
    CustomerProject(double, double, double);

    void setHours(double);
    double getHours();
    void setMaterials(double);
    double getMaterials();
    void setTransportation(double);
    double getTransportation();

    virtual double billAmount() = 0;
};

#endif /* CustomerProject_hpp */
