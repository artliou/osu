/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 10/11/17
 ** Description: Project 3.b

 *********************************************************************/

#ifndef Taxicab_HPP
#define Taxicab_HPP

class Taxicab
{
private:
  int xCoord;
  int yCoord;
  int distanceTraveled;

public:
  Taxicab();
  Taxicab(int, int);
  int getXCoord();
  int getYCoord();
  int getDistanceTraveled();
  int moveX(int);
  int moveY(int);
};
#endif /* Taxicab_hpp */
