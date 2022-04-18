/*********************************************************************
** Author:       Jeremy Prater
** Date:         August 1, 2016
** Description:  gameObjects.hpp
*********************************************************************/

#ifndef GAME_OBJECTS_HPP
#define GAME_OBJECTS_HPP

#include "gameObject.hpp"

///////////////////////////////////////////////////////////////////////////////
//
// class gameObject...
//
// The derived classes for all objects in the game
// based off of gameObject with overloaded virtual functions
//

class gameObjectKnife : public gameObject
{
public:
    gameObjectKnife(gameSpaceController * controller) : gameObject(controller) { }
    ~gameObjectKnife() { }

    objectTypes GetObjectType();
    std::string GetName();
    std::string GetText();
    bool canTake();
    bool canUseItemOnTarget(gameObject * object);
    void useItem(gameObject * object);
};
    
class gameObjectChest : public gameObject
{
private:
    bool chestOpened;

public:
    gameObjectChest(gameSpaceController * controller) : gameObject(controller) { chestOpened=false; }
    ~gameObjectChest() { }

    void OpenChest();
    bool GetChestOpen();
    objectTypes GetObjectType();
    std::string GetText();
    std::string GetName();
};

class gameObjectLock : public gameObject
{
private:
    bool lockBroken;
public:
    gameObjectLock(gameSpaceController * controller) : gameObject(controller) { lockBroken = false; }
    ~gameObjectLock() { }

    void BreakLock();
    bool GetLockBroken();
    objectTypes GetObjectType();
    std::string GetText();
    std::string GetName();
};

class gameObjectCrystalOrb : public gameObject
{
public:
    gameObjectCrystalOrb(gameSpaceController * controller) : gameObject(controller) { }
    ~gameObjectCrystalOrb() { }

    objectTypes GetObjectType();
    std::string GetName();
    std::string GetText();
    bool canTake();
    bool canUseItemOnTarget(gameObject * object);
    void useItem (gameObject * object);
};

class gameObjectFlower : public gameObject
{
public:
    gameObjectFlower(gameSpaceController * controller) : gameObject(controller) { }
    ~gameObjectFlower() { }

    objectTypes GetObjectType();
    std::string GetName();
    std::string GetText();
    bool canTake();
    bool canUseItemOnTarget(gameObject * object);
    void useItem(gameObject * object);
};

class gameObjectTeaPot : public gameObject
{
public:
    gameObjectTeaPot(gameSpaceController * controller) : gameObject(controller) { }
    ~gameObjectTeaPot() { }

    objectTypes GetObjectType();
    std::string GetName();
    std::string GetText();
};

class gameObjectElixer : public gameObject
{
public:
    gameObjectElixer(gameSpaceController * controller) : gameObject(controller) { }
    ~gameObjectElixer() { }

    objectTypes GetObjectType();
    std::string GetName();
    std::string GetText();
    bool canTake();
    bool canUseItemOnTarget(gameObject * object);
    void useItem(gameObject * object);
};

class gameObjectStarFish : public gameObject
{
public:
    gameObjectStarFish(gameSpaceController * controller) : gameObject(controller) { }
    ~gameObjectStarFish() { }

    objectTypes GetObjectType();
    std::string GetName();
    std::string GetText();
    bool canTalk();
    std::string talk();
};

class gameObjectSquirtle : public gameObject
{
public:
    gameObjectSquirtle(gameSpaceController * controller) : gameObject(controller) { }
    ~gameObjectSquirtle() { }

    objectTypes GetObjectType();
    std::string GetName();
    std::string GetText();
    bool canTalk();
    std::string talk();
};

class gameObjectStarmie : public gameObject
{
public:
    gameObjectStarmie(gameSpaceController * controller) : gameObject(controller) { }
    ~gameObjectStarmie() { }

    objectTypes GetObjectType();
    std::string GetName();
    std::string GetText();
    bool canTalk();
    std::string talk();
};

class gameObjectGem : public gameObject
{
public:
    gameObjectGem(gameSpaceController * controller) : gameObject(controller) { }
    ~gameObjectGem() { }

    objectTypes GetObjectType();
    std::string GetName();
    std::string GetText();
    bool canTake();
};

class gameObjectGemKey : public gameObject
{
public:
    gameObjectGemKey(gameSpaceController * controller) : gameObject(controller) { }
    ~gameObjectGemKey() { }

    objectTypes GetObjectType();
    std::string GetName();
    std::string GetText();
    bool canUseItemOnTarget(gameObject * object);
    void useItem (gameObject * object);
};

class gameObjectOrbHole : public gameObject
{
private:
    bool hasOrb;
public:
    gameObjectOrbHole(gameSpaceController * controller) : gameObject(controller) { hasOrb = false; }
    ~gameObjectOrbHole() { }

    objectTypes GetObjectType();
    std::string GetName();
    std::string GetText();
    void SetOrb();
    bool HasOrb();    
};

class gameObjectStick : public gameObject
{
public:
    gameObjectStick(gameSpaceController * controller) : gameObject(controller) { }
    ~gameObjectStick() { }

    objectTypes GetObjectType();
    std::string GetName();
    std::string GetText();
    bool canTake();
    bool canUseItemOnTarget(gameObject * object);
    void useItem(gameObject * object);
};

class gameObjectLantern : public gameObject
{
private:
    bool hasStick;
public:
    gameObjectLantern(gameSpaceController * controller) : gameObject(controller) { hasStick = false; }
    ~gameObjectLantern() { }

    objectTypes GetObjectType();
    std::string GetName();
    std::string GetText();
    bool canTake();

    void SetStick();
    bool HasStick();
};

class gameObjectMagicDoor : public gameObject
{
private:
    bool doorKey;
public:
    gameObjectMagicDoor(gameSpaceController * controller) : gameObject(controller) { doorKey = false; }
    ~gameObjectMagicDoor() { }

    objectTypes GetObjectType();
    std::string GetName();
    std::string GetText();
    void SetKey();
    bool HasKey();
};

#endif // GAME_OBJECTS_HPP