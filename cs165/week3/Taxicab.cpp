/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 10/11/17
 ** Description: Project 3.b

 *********************************************************************/

#include "Taxicab.hpp"
#include <cmath>
#include <iostream>
#include <string>
using namespace std;

Taxicab::Taxicab()
{
  xCoord = 0;
  yCoord = 0;
  distanceTraveled = 0;
}

Taxicab::Taxicab(int x, int y)
{
  xCoord = x;
  yCoord = y;
}

int Taxicab::getXCoord()
{
  return xCoord;
}

int Taxicab::getYCoord()
{
  return yCoord;
}

int Taxicab::getDistanceTraveled()
{
  return distanceTraveled;
}

int Taxicab::moveX(int x)
{
  xCoord = xCoord + x;

  distanceTraveled = distanceTraveled + abs(x);
}

int Taxicab::moveY(int y)
{
  yCoord = yCoord + y;
  distanceTraveled = distanceTraveled + abs(y);
}

// int main()
// {
//   Taxicab cab1;
//   Taxicab cab2(5, -8);
//   cab1.moveX(3);
//   cab1.moveY(-4);
//   cab1.moveX(-1);
//   cout << cab1.getDistanceTraveled() << endl;
//   cab2.moveY(7);
//   cout << cab2.getYCoord() << endl;
//   return 0;
// }
