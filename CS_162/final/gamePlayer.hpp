/*********************************************************************
** Author:       Jeremy Prater
** Date:         August 1, 2016
** Description:  gamePlayer.hpp
*********************************************************************/

#ifndef GAME_PLAYER_HPP
#define GAME_PLAYER_HPP

#include "classDecl.hpp"
#include "gameSpace.hpp"

#define NUM_ITEMS_INVENTORY 5

///////////////////////////////////////////////////////////////////////////////
//
// class gamePlayer
//
// The class for the gamePlayer
//

class gamePlayer
{
private:
    gameSpace * currentSpace;
    gameObject * backpackItems[NUM_ITEMS_INVENTORY];
    gameObject * recycleItems[NUM_ITEMS_INVENTORY];
    bool gameWon;

    // This is a 1:1 mapping to gameSpaceDescription::connectedSpaces
    gameSpaceLocation possibleSpaces[4];
    gameSpaceController * gameSpaceControllerInstance;

public:
    gamePlayer (gameSpaceController * instance);
    ~gamePlayer();

    void CreateObjectInBackpack(objectTypes type);
    bool MoveObjectToBackpack (gameObject * object);
    void DestroyObjectInBackpack (gameObject * object);
    void SortAndRecycleItems();

    gameObject ** GetBackpack();
    gameSpace * GetCurrentSpace();

    void SetWin();
    bool GameWon();

    bool CanMoveToSpace (gameSpaceLocation testLocation);
    bool MoveToSpace (gameSpaceLocation moveLocation);

    bool CanTakeItem(gameObject * object);
    void TakeItem(gameObject * object);

    bool CanUseItem(gameObject * object);
    void UseItem(gameObject * object);    
};

#endif // GAME_PLAYER_HPP