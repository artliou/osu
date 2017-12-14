/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/15/17
 ** Description: Project 8.b

 *********************************************************************/

#include "CustomerProject.hpp"

CustomerProject::CustomerProject(double hours, double materials, double transportation)
{
    setHours(hours);
    setMaterials(materials);
    setTransportation(transportation);
}

void CustomerProject::setHours(double hoursIn)
{
    hours = hoursIn;
}

double CustomerProject::getHours()
{
    return hours;
}

void CustomerProject::setMaterials(double materialsIn)
{
    materials = materialsIn;
}

double CustomerProject::getMaterials()
{
    return materials;
}

void CustomerProject::setTransportation(double transportationIn)
{
    transportation = transportationIn;
}

double CustomerProject::getTransportation()
{
    return transportation;
}
