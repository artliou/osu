/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 10/11/17
 ** Description: Project 3.c

 *********************************************************************/

#include "Team.hpp"
#include "Player.hpp"

Team::Team(Player pointIn, Player shootingIn, Player smallIn, Player powerIn, Player centerIn)
{
  setPointGuard(pointIn);
  setShootingGuard(shootingIn);
  setSmallForward(smallIn);
  setPowerForward(powerIn);
  setCenter(centerIn);
}

void Team::setPointGuard(Player pointIn)
{
  PointG = pointIn;
}

Player Team::getPointGuard()
{
  return PointG;
}

void Team::setShootingGuard(Player shootingIn)
{
  ShootingG = shootingIn;
}

Player Team::getShootingGuard()
{
  return ShootingG;
}

void Team::setSmallForward(Player smallIn)
{
  SmallF = smallIn;
}

Player Team::getSmallForward()
{
  return SmallF;
}
void Team::setPowerForward(Player powerIn)
{
  PowerF = powerIn;
}

Player Team::getPowerForward()
{
  return PowerF;
}

void Team::setCenter(Player centerIn)
{
  Center = centerIn;
}

Player Team::getCenter()
{
  return Center;
}

int Team::totalPoints()
{
  return PointG.getPoints() + ShootingG.getPoints() + SmallF.getPoints() + PowerF.getPoints() + Center.getPoints();
}

// int main()
// {
//   Player p1("Charlotte", 24, 10, 7);
//   Player p2("Emily", 21, 13, 9);
//   Player p3("Anne", 20, 10, 8);
//   Player p4("Jane", 19, 10, 10);
//   Player p5("Mary", 18, 11, 8);
//   p5.setRebounds(12);

//   Team team1(p1, p2, p3, p4, p5);

//   Player p = team1.getShootingGuard();
//   cout << p.getName() << endl;

//   cout << p.getPoints() << endl;
//   Player a = team1.getPowerForward();
//   cout << a.getPoints() << endl;
// }
