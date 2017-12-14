/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 10/11/17
 ** Description: Project 3.c

 *********************************************************************/

#include "Player.hpp"

Player::Player()
{
  name = "";
  points = -1;
  rebounds = -1;
  assists = -1;

  // setName("");
  // setPoints(-1);
  // setRebounds(-1);
  // setAssists(-1);
}

Player::Player(std::string nameIn, int pointsIn, int reboundsIn, int assistsIn)
{
  setName(nameIn);
  setPoints(pointsIn);
  setRebounds(reboundsIn);
  setAssists(assistsIn);
}

void Player::setName(std::string nameIn)
{
  name = nameIn;
}

std::string Player::getName()
{
  return name;
}

void Player::setPoints(int pointsIn)
{
  points = pointsIn;
}

int Player::getPoints()
{
  return points;
}

void Player::setRebounds(int reboundsIn)
{
  rebounds = reboundsIn;
}

int Player::getRebounds()
{
  return rebounds;
}

void Player::setAssists(int assistsIn)
{
  assists = assistsIn;
}

int Player::getAssists()
{
  return assists;
}

// int main()
// {
//   Player p1("Charlotte", 24, 10, 7);
//   Player p2("Emily", 21, 13, 9);
//   Player p3("Anne", 20, 10, 8);
//   Player p4("Jane", 19, 10, 10);
//   Player p5("Mary", 18, 11, 8);
//   p5.setRebounds(12);

//   cout << p3.getName() << endl;
// }
