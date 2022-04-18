/*********************************************************************
** Author:       Jeremy Prater
** Date:         August 1, 2016
** Description:  gameSpace.cpp
*********************************************************************/

#include <string.h>
#include "gameSpace.hpp"
#include "gameObjects.hpp"
#include "lib_flip_display.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Sequence of events to complete game.
//
// 1. Goto trail 4, get Flowers
// 2. Goto trail 2, get stick
// 3. Goto cabin, use flowers on teapot
// 4. Take knife
// 5. Use knife on lock
// 6. Goto cabin basement, use knife on chest
// 7. Take lantern and crystal orb
// 8. Goto river, use Elixer on Starfish
// 9. Goto pont, talk to Squirtle
// 10. Use knife of gem
// 11. Use stick on lantern
// 11. Goto cave
// 12. Use orb on orb holder, use key on gem.
// 13. Goto cave room

struct gameSpaceDescription gameSpace::gameSpaceDescriptions [] = {

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Game Space : Enchanted Forest
    //
    // Connects to:
    //         Trail 1
    //         Trail 2
    //         Trail 3
    //
    // Contains Objects:
    //         None
    //

    {"Enchanted Forest", gameSpaceLocationForest,
    {gameSpaceLocationTrail1, gameSpaceLocationTrail2, gameSpaceLocationTrail3, gameSpaceLocationInvalid},
    {objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid}},

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Game Space : Forest Trail 1
    //
    // Connects to:
    //         Forest
    //         River
    //         Trail 4
    //
    // Contains Objects:
    //         None
    //

    {"Nice smooth trail", gameSpaceLocationTrail1,
    {gameSpaceLocationForest, gameSpaceLocationRiver, gameSpaceLocationTrail4, gameSpaceLocationInvalid},
    {objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid}},

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Game Space : Forest Trail 2
    //
    // Connects to:
    //         Forest
    //         Cabin
    //
    // Contains Objects:
    //         Stick
    //

    {"Overgrown trail with old stones", gameSpaceLocationTrail2,
    {gameSpaceLocationForest, gameSpaceLocationCabin, gameSpaceLocationInvalid, gameSpaceLocationInvalid},
    {objectTypeStick, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid}},

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Game Space : Forest Trail 3
    //
    // Connects to:
    //         Forest
    //         Cave
    //         Trail 4
    //
    // Contains Objects:
    //         None
    //

    {"Trail with over hanging trees", gameSpaceLocationTrail3,
    {gameSpaceLocationForest, gameSpaceLocationTrail4, gameSpaceLocationCave, gameSpaceLocationInvalid},
    {objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid}},

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Game Space : Forest Trail 4
    //
    // Connects to:
    //         Trail 1
    //         Trail 3    
    //
    // Contains Objects:
    //         Flowers
    //

    {"Trail with over small clearing", gameSpaceLocationTrail4,
    {gameSpaceLocationTrail3, gameSpaceLocationTrail1, gameSpaceLocationInvalid, gameSpaceLocationInvalid},
    {objectTypeFlower, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid}},

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Game Space : River
    //
    // Connects to:
    //         Pond
    //         Trail 1
    //
    // Contains Objects:
    //         Starfish
    //

    {"A river", gameSpaceLocationRiver,
    {gameSpaceLocationTrail1, gameSpaceLocationPond, gameSpaceLocationInvalid, gameSpaceLocationInvalid},
    {objectTypeStarFish, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid}},

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Game Space : Pond
    //
    // Connects to:
    //         Cabin
    //         River
    //
    // Contains Objects:
    //         Squirtle
    //

    {"A pond with some fish", gameSpaceLocationPond,
    {gameSpaceLocationRiver, gameSpaceLocationCabin, gameSpaceLocationInvalid, gameSpaceLocationInvalid},
    {objectTypeSquirtle, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid}},

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Game Space : Cabin
    //
    // Connects to:
    //         Trail 2
    //         Pond
    //         Cabin Basement
    //
    // Contains Objects:
    //         Teapot, Lock
    //

    {"An abandonded log cabin.", gameSpaceLocationCabin,
    {gameSpaceLocationTrail2, gameSpaceLocationPond, gameSpaceLocationCabinBasement, gameSpaceLocationInvalid},
    {objectTypeTeaPot, objectTypeLock, objectTypeKnife, objectTypeInvalid, objectTypeInvalid}},

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Game Space : Cabin Basement
    //
    // Connects to:
    //         Cabin
    //
    // Contains Objects:
    //         Lantern, Chest
    //

    {"Secret basement in cabin.", gameSpaceLocationCabinBasement,
    {gameSpaceLocationCabin, gameSpaceLocationInvalid, gameSpaceLocationInvalid, gameSpaceLocationInvalid},
    {objectTypeLantern, objectTypeChest, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid}},

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Game Space : Cave
    //
    // Connects to:
    //         Trail 3
    //         Cave Room
    //
    // Contains Objects:
    //         Magic Door, Orb holder
    //

    {"A dark cave.", gameSpaceLocationCave,
    {gameSpaceLocationTrail3, gameSpaceLocationCaveRoom, gameSpaceLocationInvalid, gameSpaceLocationInvalid},
    {objectTypeOrbHole, objectTypeMagicDoor, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid}},

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Game Space : Cave Room
    //
    // Connects to:
    //         Cave
    //
    // Contains Objects:
    //         None
    //

    {"A room in the cave with a sky light.", gameSpaceLocationCaveRoom,
    {gameSpaceLocationCave, gameSpaceLocationInvalid, gameSpaceLocationInvalid, gameSpaceLocationInvalid},
    {objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid}},

    /////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    // Game Space : Invalid - This is used to signal the  end of the gameSpaceDescription array
    //
    // Connects to:
    //         None
    //
    // Contains Objects:
    //         None
    //

    {"EndTerminator", gameSpaceLocationInvalid,
    {gameSpaceLocationInvalid, gameSpaceLocationInvalid, gameSpaceLocationInvalid, gameSpaceLocationInvalid},
    {objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid, objectTypeInvalid}},
};

///////////////////////////////////////////////////////////////////////////////
//
// gameSpace::gameSpace(const gameSpaceDescription * spaceDesc, gameSpaceController * controller)
//
// gameSpace constructor
//
// Parameters:
//        const gameSpaceDescription * spaceDesc - the description of the location
//        gameSpaceController * Controller - The gamespace controller
//
// Return:
//        None
//

gameSpace::gameSpace(const gameSpaceDescription * spaceDesc, gameSpaceController * controller)
{
    DebugConsole::debug_print (1, false, COLOR_WHITE, "Creating gameSpace (%d) %s\n", spaceDesc->thisSpace, spaceDesc->spaceName.c_str());
    Controller = controller;
    spaceDescription.spaceName = spaceDesc->spaceName;
    spaceDescription.thisSpace = spaceDesc->thisSpace;
    memcpy (spaceDescription.connectedSpaces, spaceDesc->connectedSpaces, sizeof (spaceDescription.connectedSpaces));
    memcpy (spaceDescription.objectsInSpace, spaceDesc->objectsInSpace, sizeof (spaceDescription.objectsInSpace));

    // Create a dynamic array of the objectsInSpace
    int objectIndex=0;
    for (objectIndex = 0; objectIndex < NUM_OBJECTS_IN_SPACE; objectIndex++)
    {
        CreateObject(spaceDescription.objectsInSpace[objectIndex]);
    }   
}

///////////////////////////////////////////////////////////////////////////////
//
// gameSpace::~gameSpace()
//
// gameSpace destructor - Delete all objects in space (dynamic objects)
//
// Parameters:
//        None
//
// Return:
//        None
//

gameSpace::~gameSpace()
{
    int currentObjectIndex = 0;
    DebugConsole::debug_print (1, true, COLOR_MAGENTA, "Destroying gameSpace %s and %d objects.\n", spaceDescription.spaceName.c_str(), objects.size());
    while (currentObjectIndex < objects.size())
    {
        DebugConsole::debug_print (1, false, COLOR_MAGENTA, "Destroying Object %s\n", objects[currentObjectIndex]->GetName().c_str());
        delete objects[currentObjectIndex++];
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// bool gameSpace::CanMoveTo(gamePlayer * player)
//
// Determine if a player can move into a space - the default is true
// Derived classes will overload this function to create custom logic
// i.e. you can only enter the cave if you have a lantern with a stick in it.
//
// Parameters:
//        None
//
// Return:
//        bool - true if the player can move to that space
//

bool gameSpace::CanMoveTo(gamePlayer * player)
{
    return true;
}

///////////////////////////////////////////////////////////////////////////////
//
// const gameSpaceDescription gameSpace::GetSpaceDescription()
//
// Returns the description structure of the space.
//
// Parameters:
//        None
//
// Return:
//        const gameSpaceDescription - The description used when creating the space
//

const gameSpaceDescription gameSpace::GetSpaceDescription()
{
    return spaceDescription;
}

///////////////////////////////////////////////////////////////////////////////
//
// std::vector<gameObject *> gameSpace::GetObjects()
//
// Returns the array of objects in the space
//
// Parameters:
//        None
//
// Return:
//        std::vector<gameObject *> - Array of objects in space.
//

std::vector<gameObject *> gameSpace::GetObjects()
{
    return objects;
}

///////////////////////////////////////////////////////////////////////////////
//
// bool gameSpace::ContainsObject (objectTypes type)
//
// Returns true if an object exists in the space.
// Objects are matched by type, not by pointer address
//
// Parameters:
//        objectTypes type - Type of object to test for.
//
// Return:
//        bool - true if that type of object exists in the space.
//

bool gameSpace::ContainsObject (objectTypes type)
{
    int currentObjectIndex = 0;
    while (currentObjectIndex < objects.size())
    {
        if (objects[currentObjectIndex]->GetObjectType() == type)
        {
            return true;
        }
        currentObjectIndex++;
    }
    return false;    
}

///////////////////////////////////////////////////////////////////////////////
//
// gameObject * gameSpace::GetObject (objectTypes type)
//
// Returns the instance of an object by object type in a space.
// Uses a linear search.
//
// Parameters:
//        objectTypes type - Type of object to get.
//
// Return:
//        gameObject * - Pointer to the object, or null if it does not exist in space.
//

gameObject * gameSpace::GetObject (objectTypes type)
{
    int currentObjectIndex = 0;
    while (currentObjectIndex < objects.size())
    {
        if (objects[currentObjectIndex]->GetObjectType() == type)
        {
            return objects[currentObjectIndex];
        }
        currentObjectIndex++;
    }
    return __null;
}

///////////////////////////////////////////////////////////////////////////////
//
// void gameSpace::RemoveObject (gameObject * object)
//
// Remove an object from a space by instance.
// Uses a linear search.
//
//        !!!!!!!!!!!! THIS DOES NOT DELETE THE OBJECT !!!!!!!!!!!!
//
// This function is used to transfer objects to the player's backpack
//
// Parameters:
//        gameObject * object - instance of object to remove from space.
//
// Return:
//        None
//

void gameSpace::RemoveObject (gameObject * object)
{
    int currentObjectIndex = 0;
    while (currentObjectIndex < objects.size())
    {
        if (objects[currentObjectIndex] == object)
        {
            objects.erase (objects.begin() + currentObjectIndex);
            return;
        }
        currentObjectIndex++;
    }
    
}

///////////////////////////////////////////////////////////////////////////////
//
// void gameSpace::RemoveObject (gameObject * object)
//
// Delete an object from a space by instance.
// Uses a linear search.
//
// Parameters:
//        gameObject * object - instance of object to delete from space.
//
// Return:
//        None
//

void gameSpace::DestroyObject (gameObject * object)
{
    int currentObjectIndex = 0;
    while (currentObjectIndex < objects.size())
    {
        if (objects[currentObjectIndex] == object)
        {
            delete objects[currentObjectIndex];
            objects.erase (objects.begin() + currentObjectIndex);
            return;
        }
        currentObjectIndex++;        
    }
    
}

///////////////////////////////////////////////////////////////////////////////
//
// void gameSpace::CreateObject (objectTypes type)
//
// Create a new object in the space of type (type)
//
// Parameters:
//        objectTypes type - Type of the new object to create.
//
// Return:
//        None
//

void gameSpace::CreateObject (objectTypes type)
{
    gameObject * newObject = gameObject::CreateObjectFromType(type, Controller);
    if (newObject != __null)
    {
        DebugConsole::debug_print (1, false, COLOR_WHITE, "Creaing Object %s\n", newObject->GetName().c_str());
        objects.push_back (newObject);
    }
}