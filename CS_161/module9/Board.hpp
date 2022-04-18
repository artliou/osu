/*********************************************************************
** Author:       Jeremy Prater
** Date:         May 24, 2016
** Description:  Module 9 assignment
*********************************************************************/

#ifndef BOARD_HPP
#define BOARD_HPP

/*********************************************************************
** Description: Assignment 9
**
** class definition for Board
**
*********************************************************************/

typedef enum gameState_e
{
  X_WON,
  O_WON,
  DRAW,
  UNFINISHED
} gameState_e;

typedef enum playerTurn_e
{
  NO_PLAYER = 0,
  X_TURN    = 1,
  O_TURN    = 2
} playerTurn_e;

class Board
{
private:
  unsigned char board[3][3];
  gameState_e currentGameState;
  playerTurn_e currentPlayerTurn;

public:
  gameState_e gameState(void);
  playerTurn_e gamePlayer(void);
  bool makeMove (int x, int y);
  Board (playerTurn_e startingPlayer);

  void printBoard();
  char getPieceHelper(int x, int y);

  bool CheckWinner (playerTurn_e checkPlayer);
  bool CheckDraw(void);
};

#endif // BOARD_HPP
