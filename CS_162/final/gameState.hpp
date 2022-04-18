/*********************************************************************
** Author:       Jeremy Prater
** Date:         August 1, 2016
** Description:  gameState.hpp
*********************************************************************/

#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "classDecl.hpp"
#include "gameSpace.hpp"
#include "gameObject.hpp"


///////////////////////////////////////////////////////////////////////////////
//
// class gameSpaceController
//
// Current state of the game. Controls user input and win/lose conditions.
//

class gameState
{
private:
    gameSpaceController * Controller;
    gamePlayer * Player;
    int MovesLeft;

public:
    std::string PrintRound();
    void InteractObject (gameObject * object, bool inPack);
    void GameLoop();

    gameState();
    ~gameState();
};

#endif // GAME_STATE_HPP