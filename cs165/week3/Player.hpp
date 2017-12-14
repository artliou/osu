/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 10/11/17
 ** Description: Project 3.c

 *********************************************************************/

#ifndef Player_HPP
#define Player_HPP

#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

class Player
{
private:
  std::string name;
  int points;
  int rebounds;
  int assists;

public:
  Player();
  Player(std::string, int, int, int);

  void setName(std::string);
  std::string getName();
  void setPoints(int);
  int getPoints();
  void setRebounds(int);
  int getRebounds();
  void setAssists(int);
  int getAssists();
};
#endif /* Player_hpp */
