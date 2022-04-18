/*********************************************************************
** Author:       Jeremy Prater
** Date:         August 1, 2016
** Description:  gameSpaceController.hpp
*********************************************************************/

#ifndef GAME_SPACE_CONTROLLER_HPP
#define GAME_SPACE_CONTROLLER_HPP

#include "gameSpace.hpp"

///////////////////////////////////////////////////////////////////////////////
//
// class gameSpaceController
//
// A class that is used as a data transport layer between gameState/gameObject/gamePlayer
//

class gameSpaceController
{
private:
    std::vector<gameSpace *> gameSpaces;
    gameSpace * currentSpace;
    gamePlayer * Player;

public:
    gameSpaceController();
    ~gameSpaceController();
    
    gameSpace * GetGameSpaceByType(gameSpaceLocation location);
    void SetPlayer (gamePlayer * plaer);
    gamePlayer * GetPlayer();
    void SetCurrentSpace (gameSpace * space);
    gameSpace * GetCurrentSpace();
};

#endif // GAME_SPACE_CONTROLLER_HPP