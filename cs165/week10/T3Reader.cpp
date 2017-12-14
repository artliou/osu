/*********************************************************************
 ** Author: Arthur Liou
** Date: 11/30/17
** Description: Project 10.a

 *********************************************************************/

#include "T3Reader.hpp"
#include <iostream>
#include <fstream>
#include <string>

using std::ifstream;
using std::cout;
using std::endl;

//Constructor that takes a char and determines who has the first turn
T3Reader::T3Reader(char firstPlayer) {
    playerTurn = firstPlayer;
}

//Accepts a string parameter that gives the name of the game file.
//It will then read the file contents and use makeMove to execute moves written in the game file. It will return false if any of the moves is on an occupied square, or if there are additional moves after the game is finished. Otherwise it returns true.
bool T3Reader::readGameFile(string fileName) {
    ifstream inputFile;
    inputFile.open(fileName.c_str());

    if (inputFile) {
        cout << "File Found" << endl;

        int x, y;
        bool validMove;

        // cout << "State is: " << gameBoard.gameState() << endl;

        while (gameBoard.gameState() == UNFINISHED)
        {
            inputFile >> x;
            inputFile >> y;
            // cout << "X: " << x << " Y: " << y << endl;

            validMove = gameBoard.makeMove(x, y, playerTurn);

            //Automatically return false if invalid move
            if (validMove == false)
            {
                inputFile.close();
                cout << "Err: Invalid Move" << endl;
                return false;
            }
            gameBoard.makeMove(x, y, playerTurn);

            // Switch Turns
            if (playerTurn == 'x')
                playerTurn = 'o';
            else
                playerTurn = 'x';
        } //Exit while loop when game finishes

        // Check if moves remaining after game completed.
        // If so, exit program.
        if (inputFile >> x || inputFile >> y) {
            inputFile.close();
            cout << "Err: Extra Moves" << endl;
            // gameBoard.print();
            return false;
        }
        //Close file and return true for a completed game
        inputFile.close();
        gameBoard.print();
        return true;

    } else {
        cout << "File not found." << endl;
        return false;
    }
}