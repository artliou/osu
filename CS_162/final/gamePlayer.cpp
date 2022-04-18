/*********************************************************************
** Author:       Jeremy Prater
** Date:         August 1, 2016
** Description:  gamePlayer.cpp
*********************************************************************/

#include <string.h>
#include "gamePlayer.hpp"
#include "gameSpaceController.hpp"
#include "lib_flip_display.hpp"

///////////////////////////////////////////////////////////////////////////////
//
// gamePlayer::gamePlayer(gameSpaceController * instance)
//
// gamePlayer constructor
//
// Parameters:
//        gameSpaceController * instance - instance of the gameSpaceController
//
// Return:
//        None
//

gamePlayer::gamePlayer(gameSpaceController * instance)
{
    gameSpaceControllerInstance = instance;
    memset (backpackItems, 0, sizeof (backpackItems));
    memset (recycleItems, 0, sizeof (recycleItems));
    gameWon = false;
}

///////////////////////////////////////////////////////////////////////////////
//
// gamePlayer::~gamePlayer()
//
// gamePlayer destructor - Delete any backpack items (dynamic items)
//
// Parameters:
//        None
//
// Return:
//        None
//

gamePlayer::~gamePlayer()
{
    // Delete any backpack items...
    for (int itemIndex = 0; itemIndex < NUM_ITEMS_INVENTORY; itemIndex++)
    {
        if (backpackItems[itemIndex] != __null)
        {
            delete backpackItems[itemIndex];
            backpackItems[itemIndex] = __null;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// bool gamePlayer::CanMoveToSpace (gameSpaceLocation location)
//
// Check if a player can move into a new space.
//
// Parameters:
//        gameSpaceLocation location - enumerated location to move into
//
// Return:
//        bool - true if the move is possible
//

bool gamePlayer::CanMoveToSpace (gameSpaceLocation location)
{
    // Get the target space object based on the location
    gameSpace * gameSpaceObject = gameSpaceControllerInstance->GetGameSpaceByType(location);
    // Null-check and fail
    if (gameSpaceObject == __null)
    {
        DebugConsole::debug_print (1, true, COLOR_RED, "[%s] Defaulting to false due to bad location (%d)\n", __func__, location);
        return false;
    }
    // Return the result from the space based on player conditions
    return gameSpaceObject->CanMoveTo(this);
}

///////////////////////////////////////////////////////////////////////////////
//
// bool gamePlayer::MoveToSpace (gameSpaceLocation location)
//
// Move the player into a new space.
//
// Parameters:
//        gameSpaceLocation location - enumerated location to move into
//
// Return:
//        bool - true if the move is successful
//

bool gamePlayer::MoveToSpace (gameSpaceLocation location)
{
    if (!CanMoveToSpace(location))
    {
        DebugConsole::debug_print (1, true, COLOR_YELLOW, "[%s] Attempted to move player to (%d) is not allowed by location!\n", __func__, location);
        return false;
    }  
    currentSpace = gameSpaceControllerInstance->GetGameSpaceByType(location);
    DebugConsole::debug_print (1, true, COLOR_YELLOW, "[%s] Player moved to space %s (0x%p)!\n", __func__, currentSpace->GetSpaceDescription().spaceName.c_str(), currentSpace);
    gameSpaceControllerInstance->SetCurrentSpace (currentSpace);    
    return true;
}

///////////////////////////////////////////////////////////////////////////////
//
// gameObject ** gamePlayer::GetBackpack()
//
// Get a pointer to the backback items
//
// Parameters:
//        None
//
// Return:
//        gameObject ** - pointer to backpack objects (gameObject[NUM_ITEMS_INVENTORY] *)
//

gameObject ** gamePlayer::GetBackpack()
{
    return backpackItems;
}

///////////////////////////////////////////////////////////////////////////////
//
// gameSpace * gamePlayer::GetCurrentSpace()
//
// Get a pointer to the current space
//
// Parameters:
//        None
//
// Return:
//        gameSpace * - gameSpace object that is the current location of the player
//

gameSpace * gamePlayer::GetCurrentSpace()
{
    return currentSpace;
}

///////////////////////////////////////////////////////////////////////////////
//
// bool gamePlayer::GameWon()
//
// Get the status of the player winning the game
//
// Parameters:
//        None
//
// Return:
//        bool - true if the game is won
//

bool gamePlayer::GameWon()
{
    return gameWon;
}

///////////////////////////////////////////////////////////////////////////////
//
// void gamePlayer::SetWin()
//
// The player has won the game!
//
// Parameters:
//        None
//
// Return:
//        None
//

void gamePlayer::SetWin()
{
    gameWon = true;
}

///////////////////////////////////////////////////////////////////////////////
//
// bool gamePlayer::MoveObjectToBackpack (gameObject * object)
//
// Move an instance of an object from a space into the backback
//
// Parameters:
//        gameObject * object - Object to place in backpack
//
// Return:
//        bool - true if the move was successful
//             - false if the backpack is full (this should never happen!)
//

bool gamePlayer::MoveObjectToBackpack (gameObject * object)
{
    for (int currentObject = 0; currentObject < NUM_ITEMS_INVENTORY; currentObject++)
    {
        if (backpackItems[currentObject] == __null)
        {
            backpackItems[currentObject] = object;
            return true;
        }
    }
    // This 'SHOULD' never happen!
    DebugConsole::debug_print (0, true, COLOR_RED, "\n\nThe backpack is full!\nPlease use some items before picking up %s!\n\n", object->GetName().c_str());
    return false;
}

///////////////////////////////////////////////////////////////////////////////
//
// void gamePlayer::DestroyObjectInBackpack (gameObject * object)
//
// Move an instance of an object from the backpack into the 'recycle bin'
//
// The recycbin is a 1:1 mapping of the backpack. This function is needed
// because you can not delete an object inside of its own function
// --- delete this; is not allowed
// We simply place an object in the recycle bin, and every turn, we call
// SortAndRecycleItems which deletes those objects safely.
//
// Parameters:
//        gameObject * object - Object to destroy
//
// Return:
//        None
//

void gamePlayer::DestroyObjectInBackpack (gameObject * object)
{
    for (int currentObject = 0; currentObject < NUM_ITEMS_INVENTORY; currentObject++)
    {
        if (backpackItems[currentObject] == object)
        {
            //delete object; <-- Not allowed because this function can be called from within object's context
            recycleItems[currentObject] = backpackItems[currentObject]; 
            backpackItems[currentObject] = __null;
            return;
        }
    }    
}

///////////////////////////////////////////////////////////////////////////////
//
// void gamePlayer::CreateObjectInBackpack (objectTypes type)
//
// Create a new object in an empty backpack slot.
//
// This should never fail because there is no game state where the backpack is
// full and a new object is trying to be added.
//
// Parameters:
//        objectType type - Type of object to create
//
// Return:
//        None
//

void gamePlayer::CreateObjectInBackpack (objectTypes type)
{
    for (int currentObject = 0; currentObject < NUM_ITEMS_INVENTORY; currentObject++)
    {
        if (backpackItems[currentObject] == __null)
        {
            gameObject * newObject = gameObject::CreateObjectFromType (type, gameSpaceControllerInstance);
            DebugConsole::debug_print (1, false, COLOR_WHITE, "Creaing Object %s in backpack\n", newObject->GetName().c_str());
            backpackItems[currentObject] = newObject;
            return;
        }
    }    
}

///////////////////////////////////////////////////////////////////////////////
//
// void gamePlayer::SortAndRecycleItems()
//
// This is a two purpose function (as if the name wasn't helpful enough)
//
// 1. Delete any items in the recycleItems
// 2. Move all items in to the lowest indices in the backpack
//    The game uses an index based system for interacting with items, so all items
//    must be zero-index based
//
//    Good: | Item 1 | Item 2 | Item 3 |  NULL  |  NULL  |
//    Bad:  | Item 1 |  NULL  | Item 2 |  NULL  | Item 3 |
//
// Parameters:
//        None
//
// Return:
//        None
//

void gamePlayer::SortAndRecycleItems()
{
    for (int currentObject = 0; currentObject < NUM_ITEMS_INVENTORY; currentObject++)
    {
        if (recycleItems[currentObject] != __null)
        {
            delete recycleItems[currentObject];
            recycleItems[currentObject] = __null; 
        }
    }        
    int numItemsInBackpack = 0;
    for (int currentObject = 0; currentObject < NUM_ITEMS_INVENTORY; currentObject++)
    {

        if (backpackItems[currentObject] != __null)
        {
            numItemsInBackpack++;
        }
    }
    for (int currentObject = 0; currentObject < numItemsInBackpack; currentObject++)
    {
        if (backpackItems[currentObject] == __null)
        {
            for (int nextObject = currentObject; nextObject < NUM_ITEMS_INVENTORY; nextObject++)
            {
                if (backpackItems[nextObject] != __null)
                {
                    gameObject * swapObject = backpackItems[nextObject];
                    backpackItems[nextObject] = backpackItems[currentObject];
                    backpackItems[currentObject] = swapObject;
                    break;
                }                   
            }
        }        
    }
}