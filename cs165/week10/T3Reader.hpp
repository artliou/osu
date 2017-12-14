/*********************************************************************
 ** Author: Arthur Liou
** Date: 11/30/17
 ** Description: Project 10.a

 *********************************************************************/

#ifndef T3Reader_hpp
#define T3Reader_hpp

#include "Board.hpp"
#include <iostream>

class T3Reader {
private:
    char playerTurn;
    Board gameBoard;
public:
    T3Reader(char);
    bool readGameFile(string);
};
#endif /* T3Reader_hpp */
