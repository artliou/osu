/*********************************************************************
** Author:       Jeremy Prater
** Date:         May 24, 2016
** Description:  Module 9 assignment
*********************************************************************/
#include "Board.hpp"
#include "TicTacToe.hpp"

#include <iostream>
#include <string>

/*********************************************************************
** Description: Assignment 9
**
** Implementation for TicTacToe.cpp
**
*********************************************************************/

/////////////////////////////////////////////////////////////////
//
// TicTacToe constructors
//

/////////////////////////////////////////////////////////////////
//
// TicTacToe::TicTacToe()
//
// Class constructor with first player
//

TicTacToe::TicTacToe(char firstMove)
{
  if ((firstMove == 'x') || (firstMove == 'X'))
  {
    gameBoard = new Board (X_TURN);
  }
  else if ((firstMove == 'o') || (firstMove == 'O'))
  {
    gameBoard = new Board (O_TURN);
  }
  else
  {
    gameBoard = 0;
  }
}

/////////////////////////////////////////////////////////////////
//
// TicTacToe::~TicTacToe()
//
// Class destructor
//

TicTacToe::~TicTacToe()
{
  if (gameBoard != 0)
  {
    delete gameBoard;
  }
}

/////////////////////////////////////////////////////////////////
//
// void TicTacToe::play ()
//
// Main game loop
//

void TicTacToe::play()
{
  int currentRound = 1;
  bool inputGood = false;
  int playX = 0;
  int playY = 0;

  if (gameBoard == 0)
  {
    return;
  }

  while (gameBoard->gameState() == UNFINISHED)
  {
    std::cout << "\n\n -- Round : " << currentRound << std::endl;
    std::cout << " -- Player : ";

    if (gameBoard->gamePlayer() == X_TURN)
    {
      std::cout << "X";
    }
    else if (gameBoard->gamePlayer() == O_TURN)
    {
      std::cout << "O";
    }
    std::cout << std::endl << std::endl;

    gameBoard->printBoard();

    inputGood = false;
    while (!inputGood)
    {
      std::cout << "Enter coordinates to play :";
      std::cin >> playX >> playY;
      if (!std::cin.good())
      {
        std::cin.clear();
        std::cin.ignore ();
      }
      else
      {
        if (((playX >= 0) && (playX <= 2)) && ((playY >= 0) && (playY <= 2)))
        {
          inputGood = true;
        }
      }
    }

    if (gameBoard->makeMove (playX, playY) == false)
    {
      std::cout << std::endl<< " -- Invalid move!! " << playX << ", " << playY << " is already taken!!" << std::endl;
    }
    else
    {
      currentRound++;
    }
  }

  std::cout << std::endl << std::endl << std::endl << " -- GAME OVER --" << std::endl << std::endl;
  gameBoard->printBoard();

  switch (gameBoard->gameState())
  {
    case X_WON:
    {
      std::cout << std::endl << std::endl << "X Won !!" << std::endl;
      break;
    }
    case O_WON:
    {
      std::cout << std::endl << std::endl << "O Won !!" << std::endl;
      break;
    }
    case DRAW:
    {
      std::cout << std::endl << std::endl << "Draw (cat game?)" << std::endl;
      break;
    }
  }
}

/////////////////////////////////////////////////////////////////
//
// int main()
//
// Program entry point
//

int main()
{
  TicTacToe gameTest ('x');
  gameTest.play();
  return 0;
}
