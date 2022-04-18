/*********************************************************************
** Author:       Jeremy Prater
** Date:         May 24, 2016
** Description:  Module 9 assignment
*********************************************************************/
#include "Board.hpp"

#include <iostream>
#include <string.h>

/*********************************************************************
** Description: Assignment 9
**
** Implementation for Board.cpp
**
*********************************************************************/

/////////////////////////////////////////////////////////////////
//
// Board constructors
//

/////////////////////////////////////////////////////////////////
//
// Board::Board()
//
// Class constructor with default variables
//

Board::Board (playerTurn_e startingPlayer)
{
  memset (this->board,0 ,sizeof (this->board));
  this->currentGameState = UNFINISHED;
  this->currentPlayerTurn = startingPlayer;
}

/////////////////////////////////////////////////////////////////
//
// bool makeMove(int x, int y)
//
// Input a new move to the board and update the tic-tac-toe array
//
// Return : True if a valid move is Input.
//          False is that spot is already taken by a piece.
//

bool Board::makeMove (int x, int y)
{
  // Check if x,y is a valid move.
  if (this->board[x][y] != NO_PLAYER)
  {
    return false;
  }

  // Update board...
  this->board[x][y] = this->currentPlayerTurn;

  if (this->gamePlayer() == X_TURN)
  {
    this->currentPlayerTurn = O_TURN;
  }
  else
  {
    this->currentPlayerTurn = X_TURN;
  }

  // Update gameState if required.
  if (CheckWinner (X_TURN) == true)
  {
    this->currentGameState = X_WON;
  }
  if (CheckWinner (O_TURN) == true)
  {
    this->currentGameState = O_WON;
  }
  if (CheckDraw() == true)
  {
    this->currentGameState = DRAW;
  }
  return true;
}

/////////////////////////////////////////////////////////////////
//
// gameState_e Board::gameState()
//
// Return : The current game state.
//

gameState_e Board::gameState(void)
{
  return this->currentGameState;
}

/////////////////////////////////////////////////////////////////
//
// playerTurn_e Board::gamePlayer()
//
// Return : The current players turn.
//

playerTurn_e Board::gamePlayer(void)
{
  return this->currentPlayerTurn;
}

/////////////////////////////////////////////////////////////////
//
// void Board::printBoard();
//
// Print the current board configuration to the console.
//

void Board::printBoard(void)
{
  std::cout << std::endl << std::endl;
  std::cout << "   0   1   2 \n";
  std::cout << "0  " << this->getPieceHelper(0,0) << " | "<< this->getPieceHelper(1,0) <<" | " << this->getPieceHelper(2,0) << "\n";
  std::cout << "  -----------\n";
  std::cout << "1  " << this->getPieceHelper(0,1) << " | "<< this->getPieceHelper(1,1) <<" | " << this->getPieceHelper(2,1) << "\n";
  std::cout << "  -----------\n";
  std::cout << "2  " << this->getPieceHelper(0,2) << " | "<< this->getPieceHelper(1,2) <<" | " << this->getPieceHelper(2,2) << "\n" << std::endl;
}

/////////////////////////////////////////////////////////////////
//
// char Board::getPieceHelper(int x, int y)
//
// Helper function to return the character equivalent of a piece enum.
//

char Board::getPieceHelper(int x, int y)
{
  if (this->board[x][y] == X_TURN)
  {
    return 'X';
  }
  if (this->board[x][y] == O_TURN)
  {
    return 'O';
  }
  return '.';
}

/////////////////////////////////////////////////////////////////
//
// bool Board::CheckWinner (playerTurn_e checkPlayer)
//
// Returns true if checkPlayer completed a TicTacToe
//

bool Board::CheckWinner (playerTurn_e checkPlayer)
{
  return (((this->board[0][0] == checkPlayer) && (this->board[0][1] == checkPlayer) && (this->board[0][2] == checkPlayer)) || // Horizontal TicTacToe 1
          ((this->board[1][0] == checkPlayer) && (this->board[1][1] == checkPlayer) && (this->board[1][2] == checkPlayer)) || // Horizontal TicTacToe 2
          ((this->board[2][0] == checkPlayer) && (this->board[2][1] == checkPlayer) && (this->board[2][2] == checkPlayer)) || // Horizontal TicTacToe 3

          ((this->board[0][0] == checkPlayer) && (this->board[1][0] == checkPlayer) && (this->board[2][0] == checkPlayer)) || // Vertical TicTacToe 1
          ((this->board[0][1] == checkPlayer) && (this->board[1][1] == checkPlayer) && (this->board[2][1] == checkPlayer)) || // Vertical TicTacToe 2
          ((this->board[0][2] == checkPlayer) && (this->board[1][2] == checkPlayer) && (this->board[2][2] == checkPlayer)) || // Vertical TicTacToe 3

          ((this->board[0][0] == checkPlayer) && (this->board[1][1] == checkPlayer) && (this->board[2][2] == checkPlayer)) || // X TicTacToe 1
          ((this->board[2][0] == checkPlayer) && (this->board[1][1] == checkPlayer) && (this->board[0][2] == checkPlayer)) ); // X TicTacToe 2
}

/////////////////////////////////////////////////////////////////
//
// bool Board::CheckDraw(void)
//
// Returns true if all slots are filled and no winner is declared.
//

bool Board::CheckDraw(void)
{
  bool emptySlot = false;

  for (int x=0;x<3;x++)
  {
    for (int y=0;y<3;y++)
    {
      if (this->board[x][y] == NO_PLAYER)
      {
        emptySlot = true;
      }
    }
  }

  return !emptySlot;
}
