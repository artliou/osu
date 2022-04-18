/*********************************************************************
** Author:       Jeremy Prater
** Date:         August 1, 2016
** Description:  gameSpace.hpp
*********************************************************************/

#ifndef GAME_SPACE_HPP
#define GAME_SPACE_HPP

#include <string>
#include <vector>

#include "classDecl.hpp"
#include "gameObject.hpp"

#define NUM_CONNECTED_SPACES 4
#define NUM_OBJECTS_IN_SPACE 5

///////////////////////////////////////////////////////////////////////////////
//
// enum gameSpaceLocation
//
// A list of all possible locations in the game
//

enum gameSpaceLocation
{
    gameSpaceLocationInvalid = -1,
    gameSpaceLocationForest,
    gameSpaceLocationTrail1,
    gameSpaceLocationRiver,

    gameSpaceLocationTrail2,
    gameSpaceLocationCabin,
    gameSpaceLocationCabinBasement,
    
    gameSpaceLocationTrail3,
    gameSpaceLocationCave,
    gameSpaceLocationCaveRoom,

    gameSpaceLocationTrail4,
    gameSpaceLocationPond,

    gameSpaceLocation_NumLocations
};

///////////////////////////////////////////////////////////////////////////////
//
// struct gameSpaceDescription
//
// A struture defining the meta-data that describes a game location
//

struct gameSpaceDescription
{
    std::string spaceName;
    gameSpaceLocation thisSpace;
    gameSpaceLocation connectedSpaces[NUM_CONNECTED_SPACES];
    objectTypes objectsInSpace[NUM_OBJECTS_IN_SPACE];
};

///////////////////////////////////////////////////////////////////////////////
//
// class gameSpace
//
// The abstract base class for all locations in the game
//

class gameSpace
{
protected:
    gameSpaceDescription spaceDescription;
    std::vector<gameObject *> objects;
    gameSpaceController * Controller;

public:
    static struct gameSpaceDescription gameSpaceDescriptions[];

    gameSpace(const gameSpaceDescription * spaceDesc, gameSpaceController * controller);
    ~gameSpace();

    bool ContainsObject (objectTypes type);
    gameObject * GetObject (objectTypes type);
    const gameSpaceDescription GetSpaceDescription();
    std::vector<gameObject *> GetObjects();
    void CreateObject (objectTypes type);
    void RemoveObject (gameObject * object);
    void DestroyObject (gameObject * object);
    virtual bool CanMoveTo (gamePlayer * player);
    virtual std::string GetSpaceText () = 0;
};


#endif // GAME_SPACE_HPP