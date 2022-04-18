/*********************************************************************
** Author:       Jeremy Prater
** Date:         May 24, 2016
** Description:  Module 9 assignment
*********************************************************************/

#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

/*********************************************************************
** Description: Assignment 9
**
** class definition for TicTacToe
**
*********************************************************************/

#include "Board.hpp"


class TicTacToe
{
private:
  Board * gameBoard;

public:
  TicTacToe(char firstMove);
  ~TicTacToe();
  void play();
};

#endif // TICTACTOE_HPP
