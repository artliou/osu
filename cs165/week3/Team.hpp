/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 10/11/17
 ** Description: Project 3.c

 *********************************************************************/

#ifndef Team_HPP
#define Team_HPP

// #include "Player.cpp"
#include "Player.hpp"
#include <iostream>
#include <string>
using namespace std;

class Team
{
private:
  Player PointG, ShootingG, SmallF, PowerF, Center;

public:
  Team(Player, Player, Player, Player, Player);

  void setPointGuard(Player);
  Player getPointGuard();
  void setShootingGuard(Player);
  Player getShootingGuard();
  void setSmallForward(Player);
  Player getSmallForward();
  void setPowerForward(Player);
  Player getPowerForward();
  void setCenter(Player);
  Player getCenter();
  int totalPoints();
};
#endif /* Team_hpp */
