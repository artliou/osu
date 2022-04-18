/*********************************************************************
** Author:       Jeremy Prater
** Date:         August 1, 2016
** Description:  gameObject.cpp
*********************************************************************/

#include "gameObject.hpp"
#include "gameObjects.hpp"
#include "lib_flip_display.hpp"

///////////////////////////////////////////////////////////////////////////////
//
// gameObject::gameObject(gameSpaceController * controller)
//
// gameObject constructor
//
// Parameters:
//        gameSpaceController * controller - Instance of the gameSpaceController
//                                         - Used for object-space-player interaction
//
// Return:
//        None
//

gameObject::gameObject(gameSpaceController * controller)
{
    Controller = controller;
}

///////////////////////////////////////////////////////////////////////////////
//
// gameObject::~gameObject()
//
// gameObject destructor - gameObject has no dynamic objects to clean up
//
// Parameters:
//        None
//
// Return:
//        None
//

gameObject::~gameObject()
{

}

///////////////////////////////////////////////////////////////////////////////
//
// bool gameObject::canUseItemOnTarget(gameObject * target)
//
// virtual function that returns true if an object can be used on another object.
//
// The default is false for all objects. If a specific object can be used, then
// the derived class will overload this function.
//
// Parameters:
//        gameObject * target - Object to test
//
// Return:
//        bool - true if the object can be used on (target)
//

bool gameObject::canUseItemOnTarget(gameObject * target)
{
    return false;
}

///////////////////////////////////////////////////////////////////////////////
//
// void gameObject::useItem(gameObject * target)
//
// virtual function that preforms interaction with object-space-player
//
// The default is a no-op for all objects. If a specific object can be used, then
// the derived class will overload this function and preform custom logic.
//
// Parameters:
//        gameObject * target - Object to use (this) on.
//
// Return:
//        None
//

void gameObject::useItem(gameObject * target)
{
    return;
}

///////////////////////////////////////////////////////////////////////////////
//
// bool gameObject::canTake()
//
// virtual function that returns true if an object can be picked up by the player
//
// The default is false for all objects. If a specific object can be taken, then
// the derived class will overload this function.
//
// Parameters:
//        None
//
// Return:
//        bool - true if the player can take this object
//

bool gameObject::canTake()
{
    return false;
}

///////////////////////////////////////////////////////////////////////////////
//
// bool gameObject::canTalk()
//
// virtual function that returns true if an object can talk to the player
//
// The default is false for all objects. If a specific object can talk, then
// the derived class will overload this function.
//
// Parameters:
//        None
//
// Return:
//        bool - true if the object can talk
//

bool gameObject::canTalk()
{
    return false;
}

///////////////////////////////////////////////////////////////////////////////
//
// std::string gameObject::talk()
//
// virtual function that returns the string the objects says to the player
//
// The default is an error for all objects. If a specific object can talk, then
// the derived class will overload this function with object specific text.
//
// Parameters:
//        None
//
// Return:
//        std::string - text the object says
//

std::string gameObject::talk()
{
    return "ERROR: Object can not talk!";
}

///////////////////////////////////////////////////////////////////////////////
//
// gameObject * gameObject::CreateObjectFromType (objectTypes type, gameSpaceController * Controller)
//
// static function that returns a new object of type (type) using (Controller) as the
// game space controller
//
// Parameters:
//        objectTypes type - enum of objectTypes to create
//        gameSpaceController * Controller - The gamespace controller
//                                         - This gets passed into the object's constructor
//
// Return:
//        gameObject * - Instance of a new object (type)
//

gameObject * gameObject::CreateObjectFromType (objectTypes type, gameSpaceController * Controller)
{
    gameObject * newObject = __null;
    switch (type)
    {
        case objectTypeKnife:
        {
            newObject = new gameObjectKnife(Controller);
        }
        break;
        case objectTypeChest:
        {
            newObject = new gameObjectChest(Controller);
        }
        break;
        case objectTypeLock:
        {
            newObject = new gameObjectLock(Controller);
        }
        break;
        case objectTypeCrystalOrb:
        {
            newObject = new gameObjectCrystalOrb(Controller);
        }
        break;
        case objectTypeFlower:
        {
            newObject = new gameObjectFlower(Controller);
        }
        break;
        case objectTypeTeaPot:
        {
            newObject = new gameObjectTeaPot(Controller);
        }
        break;
        case objectTypeElixer:
        {
            newObject = new gameObjectElixer(Controller);
        }
        break;
        case objectTypeStarFish:
        {
            newObject = new gameObjectStarFish(Controller);
        }
        break;
        case objectTypeSquirtle:
        {
            newObject = new gameObjectSquirtle(Controller);
        }
        break;
        case objectTypeStarmie:
        {
            newObject = new gameObjectStarmie(Controller);
        }
        break;
        case objectTypeGem:
        {
            newObject = new gameObjectGem(Controller);
        }
        break;
        case objectTypeGemKey:
        {
            newObject = new gameObjectGemKey(Controller);
        }
        break;
        case objectTypeOrbHole:
        {
            newObject = new gameObjectOrbHole(Controller);
        }
        break;
        case objectTypeStick:
        {
            newObject = new gameObjectStick(Controller);
        }
        break;
        case objectTypeLantern:
        {
            newObject = new gameObjectLantern(Controller);
        }
        break;
        case objectTypeMagicDoor:
        {
            newObject = new gameObjectMagicDoor(Controller);
        }
        break;
        default:
        {
            // Ignore invalid object.
        }
        break;
    }
    return newObject;
}