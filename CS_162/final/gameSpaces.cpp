/*********************************************************************
** Author:       Jeremy Prater
** Date:         August 1, 2016
** Description:  gameSpaces.cpp
*********************************************************************/

#include "classDecl.hpp"
#include "gameSpaces.hpp"
#include "gameObjects.hpp"
#include "gamePlayer.hpp"
#include "gameSpaceController.hpp"
#include "lib_flip_display.hpp"

////////////////////////////////////////////////////////////////////////////////////////////
//
// std::string ...::GetSpaceText()
//
// Return the text for a space.
//

std::string gameSpaceForest::GetSpaceText()
{
    static bool firstTime = true;
    std::string text = "";
    if (firstTime == true)
    {
        text += "You awake with a note in your pocket that says \n\t\"Help me, I am trapped behind a door in a room made of rock.\n\tI know who is enslaving the creature of this land.\n\tGo find my friend in the pond, he will help you.\n\tYou must hurry and free me, time is short!\n\tYou are in danger!\"\n\n";
        firstTime = false;
    }
    text += "You are in a small clearing in the woods. Light gleams through the gaps between the trees and casts moving shadows all over the ground. There are three trails that leave from this area.";
    return text;
}
std::string gameSpaceTrail1::GetSpaceText()
{
    return "";
}
std::string gameSpaceRiver::GetSpaceText()
{
    return "";
}
std::string gameSpaceTrail2::GetSpaceText()
{
    return "";
}
std::string gameSpaceCabin::GetSpaceText()
{
    return "";
}
std::string gameSpaceCabinBasement::GetSpaceText()
{
    return "";
}
std::string gameSpaceTrail3::GetSpaceText()
{
    return "";
}
std::string gameSpaceCave::GetSpaceText()
{
    return "";
}
std::string gameSpaceCaveRoom::GetSpaceText()
{
    return "";
}
std::string gameSpaceTrail4::GetSpaceText()
{
    return "";
}
std::string gameSpacePond::GetSpaceText()
{
    return "";
}

////////////////////////////////////////////////////////////////////////////////////////////
//
// bool ...::CanMoveTo(gamePlayer * player)
//
// Return true if the player can move in to a space.
//

bool gameSpaceCabinBasement::CanMoveTo(gamePlayer * player)
{
    gameObjectLock * lock = (gameObjectLock*) Controller->GetGameSpaceByType(gameSpaceLocationCabin)->GetObject(objectTypeLock);
    if (!lock->GetLockBroken())
    {
        DebugConsole::debug_print (0, true, COLOR_YELLOW, "\nThe basement door is locked.\n\n");
    }
    return lock->GetLockBroken();
}

bool gameSpaceCave::CanMoveTo(gamePlayer * player)
{
    gameObjectLantern * lantern = __null;
    for (int objectIndex = 0; objectIndex < NUM_ITEMS_INVENTORY; objectIndex++)
    {
        if ((player->GetBackpack()[objectIndex] != __null) && (player->GetBackpack()[objectIndex]->GetObjectType() == objectTypeLantern))
        {
            lantern = (gameObjectLantern*)player->GetBackpack()[objectIndex];
        }    
    }
    if (lantern == __null)
    {
        DebugConsole::debug_print (0, true, COLOR_YELLOW, "It is too dark to to in the cave.\nYou must find a light.\n\n");
        return false;
    }
    if (!lantern->HasStick())
    {
        DebugConsole::debug_print (0, true, COLOR_YELLOW, "It is too dark to to in the cave.\nYou must find something to burn in the lantern.\n\n");
    }
    return lantern->HasStick();
}

bool gameSpaceCaveRoom::CanMoveTo(gamePlayer * player)
{
    // The player must be in the Cave for this to be called
    gameSpaceCave * cave = (gameSpaceCave*)player->GetCurrentSpace();
    gameObjectOrbHole * orbHole = (gameObjectOrbHole *) cave->GetObject(objectTypeOrbHole);
    gameObjectMagicDoor * magicDoor = (gameObjectMagicDoor *) cave->GetObject(objectTypeMagicDoor);
    if (!((orbHole->HasOrb()) && (magicDoor->HasKey())))
    {
       DebugConsole::debug_print (0, true, COLOR_YELLOW, "The door is sealed shut.\n\n");
    }
    return ((orbHole->HasOrb()) && (magicDoor->HasKey()));
}