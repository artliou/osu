/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/15/17
 ** Description: Project 8.b

 *********************************************************************/

#include "RegularProject.hpp"

double RegularProject::billAmount()
{
    return (80 * getHours()) + getMaterials() + getTransportation();
}
