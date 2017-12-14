/*********************************************************************
 ** Author: Arthur Liou
 ** Date: 11/30/17
 ** Description: Project 10.a

 *********************************************************************/

#ifndef Board_hpp
#define Board_hpp
#include <iostream>
using namespace std;

enum Result {X_WON, O_WON, DRAW, UNFINISHED};

class Board {
private:
    char boardArray[3][3];
public:
    Board();
    bool makeMove(int row, int col, char playerTurn);
    Result gameState();
    void print();
};

#endif /* Board_hpp */
