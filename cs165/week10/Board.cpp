/*********************************************************************
 ** Author: Arthur Liou
** Date: 11/30/17
** Description: Project 10.a

 A tic-tac-toe game.  Board class set up a 3x3 tic-tac-toe board.
 The TicTacToe class manages the 2 player game.

 *********************************************************************/

#include "Board.hpp"

Board::Board() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            boardArray[i][j] = ' ';
}

//places an X or O at a position on the board if available. Returns true if it's empty, false if already occupied
bool Board::makeMove(int row, int col, char playerTurn) {
    if (boardArray[row][col] == ' ') {
        // cout << "Move Made: " << playerTurn << endl;
        boardArray[row][col] = playerTurn;
        return true;
    }
    return false;
}

//Checking for Game end; win conditions, across, down, diagonal, draw or no winner
Result Board::gameState() {

    if (boardArray[0][0] == 'x' && boardArray[0][1] == 'x' && boardArray[0][2] == 'x')
    {
        cout << "X Wins" << endl;
        return X_WON;
    }

    else if (boardArray[1][0] == 'x' && boardArray[1][1] == 'x' && boardArray[1][2] == 'x')
    {
        cout << "X Wins" << endl;
        return X_WON;
    }

    else if (boardArray[2][0] == 'x' && boardArray[2][1] == 'x' && boardArray[2][2] == 'x')
    {
        cout << "X Wins" << endl;
        return X_WON;
    }

    else if (boardArray[0][0] == 'x' && boardArray[1][0] == 'x' && boardArray[2][0] == 'x')
    {
        cout << "X Wins" << endl;
        return X_WON;
    }

    else if (boardArray[0][1] == 'x' && boardArray[1][1] == 'x' && boardArray[2][1] == 'x')
    {
        cout << "X Wins" << endl;
        return X_WON;
    }

    else if (boardArray[0][2] == 'x' && boardArray[1][2] == 'x' && boardArray[2][2] == 'x')
    {
        cout << "X Wins" << endl;
        return X_WON;
    }

    else if (boardArray[0][0] == 'x' && boardArray[1][1] == 'x' && boardArray[2][2] == 'x')
    {
        cout << "X Wins" << endl;
        return X_WON;
    }

    else if (boardArray[2][0] == 'x' && boardArray[1][1] == 'x' && boardArray[0][2] == 'x')
    {
        cout << "X Wins" << endl;
        return X_WON;
    }

    else if (boardArray[0][0] == 'o' && boardArray[0][1] == 'o' && boardArray[0][2] == 'o')
    {
        cout << "O Wins" << endl;
        return O_WON;
    }

    else if (boardArray[1][0] == 'o' && boardArray[1][1] == 'o' && boardArray[1][2] == 'o')
    {
        cout << "O Wins" << endl;
        return O_WON;
    }

    else if (boardArray[2][0] == 'o' && boardArray[2][1] == 'o' && boardArray[2][2] == 'o')
    {
        cout << "O Wins" << endl;
        return O_WON;
    }

    else if (boardArray[0][0] == 'o' && boardArray[1][0] == 'o' && boardArray[2][0] == 'o')
    {
        cout << "O Wins" << endl;
        return O_WON;
    }

    else if (boardArray[0][1] == 'o' && boardArray[1][1] == 'o' && boardArray[2][1] == 'o')
    {
        cout << "O Wins" << endl;
        return O_WON;
    }

    else if (boardArray[0][2] == 'o' && boardArray[1][2] == 'o' && boardArray[2][2] == 'o')
    {
        cout << "O Wins" << endl;
        return O_WON;
    }

    else if (boardArray[0][0] == 'o' && boardArray[1][1] == 'o' && boardArray[2][2] == 'o')
    {
        cout << "O Wins" << endl;
        return O_WON;
    }

    else if (boardArray[2][0] == 'o' && boardArray[1][1] == 'o' && boardArray[0][2] == 'o')
    {
        cout << "O Wins" << endl;
        return O_WON;
    }
    // If not victory then unfinished or draw
    else
    {
        //check for unused spaces
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++){
                if (boardArray[i][j] == ' ')
                {
                    // cout << "Unfinished " << endl;
                    return UNFINISHED;
                }
            }
        }
        //if unfinished isn't returned, board is full and returns draw
        cout << "Drawn " << endl;
        return DRAW;
    }
}

void Board::print() {
    cout << "  0 1 2" << endl;
    for (int i = 0; i < 3; i++) {
        cout << i << " ";
        for (int j = 0; j < 3; j++)
            cout << boardArray[i][j] << " ";
        cout << endl << endl;
    }
}
