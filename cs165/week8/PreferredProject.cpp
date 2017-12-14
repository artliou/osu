/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/15/17
 ** Description: Project 8.b

 *********************************************************************/

#include "PreferredProject.hpp"

double PreferredProject::billAmount()
{
    double hours = CustomerProject::getHours();
    double b = (0.85 * CustomerProject::getMaterials()) + (0.9 * CustomerProject::getTransportation());
    if (hours > 100)
        return 8000 + b;
    return (80 * hours) + b;
}
