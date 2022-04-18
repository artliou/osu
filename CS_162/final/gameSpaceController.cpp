/*********************************************************************
** Author:       Jeremy Prater
** Date:         August 1, 2016
** Description:  gameSpaceController.cpp
*********************************************************************/

#include "gameSpaceController.hpp"
#include "gameSpaces.hpp"
#include "gameObjects.hpp"
#include "lib_flip_display.hpp"

///////////////////////////////////////////////////////////////////////////////
//
// gameSpaceController::gameSpaceController()
//
// gameSpaceController constuctor
//
// Interates through the list of gameSpaces defined in gameSpace::gameSpaceDescriptions
//  and constructs the gameSpace object which creates gameObjects inside of it.
//
// Parameters:
//        None
//
// Return:
//        None
//

gameSpaceController::gameSpaceController()
{
    int currentSpaceIndex = 0;
    DebugConsole::debug_print(1, true, COLOR_CYAN, "Creating gameSpaces\n");
    while (gameSpace::gameSpaceDescriptions[currentSpaceIndex].thisSpace != gameSpaceLocationInvalid)
    {
        switch (gameSpace::gameSpaceDescriptions[currentSpaceIndex].thisSpace)
        {
            case gameSpaceLocationForest:
            {
                gameSpaces.push_back (new gameSpaceForest (&gameSpace::gameSpaceDescriptions[currentSpaceIndex], this));
            }
            break;
            case gameSpaceLocationTrail1:
            {
                gameSpaces.push_back (new gameSpaceTrail1 (&gameSpace::gameSpaceDescriptions[currentSpaceIndex], this));
            }
            break;
            case gameSpaceLocationRiver:
            {
                gameSpaces.push_back (new gameSpaceRiver (&gameSpace::gameSpaceDescriptions[currentSpaceIndex], this));
            }
            break;
            case gameSpaceLocationTrail2:
            {
                gameSpaces.push_back (new gameSpaceTrail2 (&gameSpace::gameSpaceDescriptions[currentSpaceIndex], this));
            }
            break;
            case gameSpaceLocationCabin:
            {
                gameSpaces.push_back (new gameSpaceCabin (&gameSpace::gameSpaceDescriptions[currentSpaceIndex], this));
            }
            break;
            case gameSpaceLocationCabinBasement:
            {
                gameSpaces.push_back (new gameSpaceCabinBasement (&gameSpace::gameSpaceDescriptions[currentSpaceIndex], this));
            }
            break;
            case gameSpaceLocationTrail3:
            {
                gameSpaces.push_back (new gameSpaceTrail3 (&gameSpace::gameSpaceDescriptions[currentSpaceIndex], this));
            }
            break;
            case gameSpaceLocationCave:
            {
                gameSpaces.push_back (new gameSpaceCave (&gameSpace::gameSpaceDescriptions[currentSpaceIndex], this));
            }
            break;
            case gameSpaceLocationCaveRoom:
            {
                gameSpaces.push_back (new gameSpaceCaveRoom (&gameSpace::gameSpaceDescriptions[currentSpaceIndex], this));
            }
            break;
            case gameSpaceLocationTrail4:
            {
                gameSpaces.push_back (new gameSpaceTrail4 (&gameSpace::gameSpaceDescriptions[currentSpaceIndex], this));
            }
            break;
            case gameSpaceLocationPond:            
            {
                gameSpaces.push_back (new gameSpacePond (&gameSpace::gameSpaceDescriptions[currentSpaceIndex], this));
            }
            break;
            default:
            {
                DebugConsole::debug_print(1, true, COLOR_YELLOW, "Attempted to create unknown gameSpace (%d).\n", gameSpace::gameSpaceDescriptions[currentSpaceIndex].thisSpace);
            }
            break;
        }
        currentSpaceIndex++;
    }
    DebugConsole::debug_print(1, true, COLOR_CYAN, "Parsed %d gameSpaceDescriptions\n", currentSpaceIndex);    
}

///////////////////////////////////////////////////////////////////////////////
//
// gameSpaceController::~gameSpaceController()
//
// gameSpaceController destructor
//
// Destroys all gameSpaces
//
// Parameters:
//        None
//
// Return:
//        None
//

gameSpaceController::~gameSpaceController()
{
    int currentSpaceIndex = 0;
    DebugConsole::debug_print(1, true, COLOR_CYAN, "Destroying gameSpaces\n");
    while (currentSpaceIndex < gameSpaces.size())
    {
        delete gameSpaces[currentSpaceIndex++];
    }    
}

///////////////////////////////////////////////////////////////////////////////
//
// gameSpace * gameSpaceController::GetGameSpaceByType(gameSpaceLocation location)
//
// Get a game space object by location
//
// Parameters:
//        gameSpaceLocation location
//
// Return:
//        gameSpace * - instance of the gameSpace, or null if it is not found.
//

gameSpace * gameSpaceController::GetGameSpaceByType(gameSpaceLocation location)
{
    int index = 0;
    while (index < gameSpaces.size())
    {
        if (gameSpaces[index]->GetSpaceDescription().thisSpace == location)
        return gameSpaces[index];
        index++;
    }
    DebugConsole::debug_print(1, true, COLOR_RED, "Unable to locate space (%d). Returning null. Program may crash!\n", location);
    return __null;
}

///////////////////////////////////////////////////////////////////////////////
//
// gameSpace * gameSpaceController::GetCurrentSpace()
//
// Returns the current space that the player has informed it is on.
//
// Parameters:
//        None
//
// Return:
//        gameSpace * - The last reported position of the player
//

gameSpace * gameSpaceController::GetCurrentSpace()
{
    return currentSpace;
}

///////////////////////////////////////////////////////////////////////////////
//
// void  gameSpaceController::SetCurrentSpace(gameSpace * space)
//
// Called by the player to update it's current gameSpace
//
// Parameters:
//        gameSpace * space - current player location
//
// Return:
//        None
//

void  gameSpaceController::SetCurrentSpace(gameSpace * space)
{
    currentSpace = space;
}

///////////////////////////////////////////////////////////////////////////////
//
// void gameSpaceController::SetPlayer (gamePlayer * player)
//
// Called by the player to pair a gameSpaceController to a player instance
//
// Parameters:
//        gamePlayer * player - instance of a gamePlayer
//
// Return:
//        None
//

void gameSpaceController::SetPlayer (gamePlayer * player)
{
    Player = player;
}
///////////////////////////////////////////////////////////////////////////////
//
// void gameSpaceController::GetPlayer ()
//
// Called by gameSpaces and gameObjects to get information about the player
//
// Parameters:
//        None
//
// Return:
//        gamePlayer * - the current player
//

gamePlayer * gameSpaceController::GetPlayer()
{
    return Player;
}