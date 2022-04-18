/*********************************************************************
** Author:       Jeremy Prater
** Date:         August 1, 2016
** Description:  gameState.cpp
*********************************************************************/

#include "gameState.hpp"
#include "gameSpaceController.hpp"
#include "gamePlayer.hpp"
#include "gameObject.hpp"
#include <iostream>
#include "lib_flip_display.hpp"

///////////////////////////////////////////////////////////////////////////////
//
// gameState::gameState()
//
// gameState constructor
//
// Creates a new class for managing the state of the game and user input
//
// Parameters:
//        None
//
// Return:
//        None
//

gameState::gameState()
{
    Controller = new gameSpaceController();
    Player = new gamePlayer(Controller);
    Controller->SetPlayer(Player);
    Player->MoveToSpace (gameSpaceLocationForest);
    MovesLeft = 50;  
}

///////////////////////////////////////////////////////////////////////////////
//
// gameState::~gameState()
//
// gameState destructor
//
// Delete the gameController and gamePlayer
//
// Parameters:
//        None
//
// Return:
//        None
//

gameState::~gameState()
{
    delete Controller;
    delete Player;
}

///////////////////////////////////////////////////////////////////////////////
//
// gameState::PrintRound()
//
// Print out the current location/objects/player data
//
//
// Parameters:
//        None
//
// Return:
//        std::string - input from user.
//

std::string gameState::PrintRound()
{
    Player->SortAndRecycleItems();
    
    DebugConsole::debug_print (0, false, COLOR_CYAN, "Moves left: ");

    if (MovesLeft <= 10)
    {
        DebugConsole::debug_print (0, true, COLOR_RED, "%d\n\n", MovesLeft);
    }
    else if (MovesLeft <= 20)
    {
        DebugConsole::debug_print (0, true, COLOR_YELLOW, "%d\n\n", MovesLeft);
    }
    else
    {
        DebugConsole::debug_print (0, true, COLOR_GREEN, "%d\n\n", MovesLeft);
    }
    

    DebugConsole::debug_print (0, true, COLOR_GREEN, "\n\n\nLocation [%s]\n\n", Controller->GetCurrentSpace()->GetSpaceDescription().spaceName.c_str());
    DebugConsole::debug_print (0, false, COLOR_WHITE, "%s\n\n\n\n\n\n", Controller->GetCurrentSpace()->GetSpaceText().c_str());

    std::string inventory = "Inventory: ";
    std::string inventoryList = "";
    bool inventoryEmpy = true;
    for (int inventoryCount = 0; inventoryCount < NUM_ITEMS_INVENTORY; inventoryCount++)
    {
        gameObject * backpackItem = Player->GetBackpack()[inventoryCount]; 
        if (backpackItem != __null)
        {
            inventoryList += std::string("\t") + std::to_string(inventoryCount + 1) + ": " + backpackItem->GetName();
            inventoryEmpy = false; 
        }
    }
    if (inventoryEmpy)
    {
        inventory = "Inventory Empty.\n\n\n";
    }

    DebugConsole::debug_print (0, true, COLOR_CYAN, "%s", inventory.c_str());
    if (!inventoryEmpy)
    {
        DebugConsole::debug_print (0, false, COLOR_WHITE, "%s\n\n", inventoryList.c_str());
    }

    DebugConsole::debug_print (0, true, COLOR_CYAN, "Moves: ", inventory.c_str());
    std::string moveList = "";
    for (int moveCount = 0; moveCount < NUM_CONNECTED_SPACES; moveCount++)
    {
        if ((Player->GetCurrentSpace()->GetSpaceDescription().connectedSpaces[moveCount] != gameSpaceLocationInvalid))
            //&& Controller->GetGameSpaceByType(Player->GetCurrentSpace()->GetSpaceDescription().connectedSpaces[moveCount])->CanMoveTo(Player))
            // This was to control which connected gameSpaces are visible to the player.
            //but it created a zero-based index issue with game locations. A better solution was to add/delete values from the gameSpace metadata which defines the connected spaces.
            // This was used to hide the CabinBasement until the lock is broken.
        {
            moveList += std::string("\t ") + std::to_string(moveCount + 1) + ": " + Controller->GetGameSpaceByType (Player->GetCurrentSpace()->GetSpaceDescription().connectedSpaces[moveCount])->GetSpaceDescription().spaceName;
        } 
    }
    DebugConsole::debug_print (0, false, COLOR_WHITE, "%s\n\n\n", moveList.c_str());

    DebugConsole::debug_print (0, true, COLOR_CYAN, "Objects in space:\n", inventory.c_str());
    if (Player->GetCurrentSpace()->GetObjects().size() > 0)
    {
        std::string objectList = "";
        for (int objectCount = 0; objectCount < Player->GetCurrentSpace()->GetObjects().size(); objectCount++)
        {
            objectList += std::string("\t ") + std::to_string(objectCount + 1) + ": " + Player->GetCurrentSpace()->GetObjects()[objectCount]->GetName() + "\n" + Player->GetCurrentSpace()->GetObjects()[objectCount]->GetText() + "\n\n";   
        }    
        DebugConsole::debug_print (0, false, COLOR_WHITE, "%s\n\n", objectList.c_str());
    }
    else
    {
        DebugConsole::debug_print (0, false, COLOR_WHITE, "None.\n\n");
    }

    DebugConsole::debug_print (0, true, COLOR_WHITE, "Commands:\n\n");
    DebugConsole::debug_print (0, false, COLOR_WHITE, "m<id> - Move to new space. Example : >m2\n");
    DebugConsole::debug_print (0, false, COLOR_WHITE, "i<id> - Interact wth inventory item. Example : >i2\n");
    DebugConsole::debug_print (0, false, COLOR_WHITE, "o<id> - Interact with object in space. Example : >o1\n");
    DebugConsole::debug_print (0, false, COLOR_WHITE, "q     - Abandon the quest.\n");
    DebugConsole::debug_print (0, false, COLOR_WHITE, "\n\nEnter Command >");
    std::string command;
    std::cin >> command;
    if (DebugConsole::GetDebugLevel() == 0)
    {
        DebugConsole::screen_clear();
    }
    return command;
}


///////////////////////////////////////////////////////////////////////////////
//
// void gameState::GameLoop()
//
// Main logic processing for gameState. Process user input and determines win/lose
//
// Parameters:
//        None
//
// Return:
//        None
//

void gameState::GameLoop()
{
    bool playing = true;
    while (playing)
    {
        const char * commandPtr = PrintRound().c_str();
        switch (commandPtr[0])
        {
            case 'q':
            case 'Q':
            {
                playing = false;
            }
            break;
            case 'm':
            case 'M':
            {
                int moveTo = atoi (&commandPtr[1]);
                if ((moveTo > 0) && (moveTo <= NUM_CONNECTED_SPACES))
                {
                    if (Player->MoveToSpace (Player->GetCurrentSpace()->GetSpaceDescription().connectedSpaces[moveTo - 1]))
                    {
                        MovesLeft--;
                        if (Player->GetCurrentSpace()->GetSpaceDescription().thisSpace == gameSpaceLocationCaveRoom)
                        {
                            // You win!
                            Player->SetWin();
                        }
                    }
                }
            }
            break;
            case 'o':
            case 'O':
            {
                int objectID = atoi (&commandPtr[1]);
                if ((objectID > 0) && (objectID <= Player->GetCurrentSpace()->GetObjects().size()))
                {
                    InteractObject (Player->GetCurrentSpace()->GetObjects()[objectID - 1], false);
                }
            }
            break;
            case 'i':
            case 'I':
            {
                int objectID = atoi (&commandPtr[1]);
                if ((objectID > 0) && (objectID <= NUM_ITEMS_INVENTORY) && (Player->GetBackpack()[objectID - 1] != __null))
                {
                    InteractObject (Player->GetBackpack()[objectID - 1], true);
                }
            }
            break;
        }

        if (Player->GameWon() == true)
        {
            playing = false;
            DebugConsole::debug_print (0, true, COLOR_GREEN, "\n\n\t\tThank you for freeing me!\n\n\tThe creatures of the forest are saved!!\n\n");
        }
        if (MovesLeft == 0)
        {
            playing = false;
            DebugConsole::debug_print (0, true, COLOR_RED, "\n\n\t\tTime is up!!\n\nThe creatures of the forest are doomed...\n\n");
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
//
// void gameState::InteractObject (gameObject * object, bool inPack)
//
// Print out the current information about the current object the user
// is interacting with. Accept input from user and process.
//
//
// Parameters:
//        None
//
// Return:
//        None
//

void gameState::InteractObject (gameObject * object, bool inPack)
{
    bool commandObject = true;
    while (commandObject == true)
    {
        DebugConsole::debug_print (0, true, COLOR_CYAN, "\n\nInteracting with [%s].\n\n", object->GetName().c_str());
        DebugConsole::debug_print (0, false, COLOR_WHITE, "\n\n%s\n\n\n", object->GetText().c_str());
        DebugConsole::debug_print (0, true, COLOR_WHITE, "\n\nCommands: \n\n");
        if (object->canTalk())
        {
            DebugConsole::debug_print (0, true, COLOR_WHITE, "t - Talk to %s\n", object->GetName().c_str());
        }
        if (object->canTake() && !inPack)
        {
            DebugConsole::debug_print (0, true, COLOR_WHITE, "g - Take to %s\n", object->GetName().c_str());
        }
        DebugConsole::debug_print (0, true, COLOR_WHITE, "u - Use %s\n", object->GetName().c_str());
        if (!inPack)
        {
            DebugConsole::debug_print (0, true, COLOR_WHITE, "c - Walk away from %s\n", object->GetName().c_str());
        }
        else
        {
            DebugConsole::debug_print (0, true, COLOR_WHITE, "c - Put %s back in backpack\n", object->GetName().c_str());
        }
        DebugConsole::debug_print (0, true, COLOR_WHITE, "\n\nEnter Command >");
        std::string command;
        std::cin >> command;
        if (DebugConsole::GetDebugLevel() == 0)
        {
            DebugConsole::screen_clear();
        }
        const char * commandPtr = command.c_str();
        switch (commandPtr[0])
        {
            case 'c':
            case 'C':
            {
                commandObject = false;
            }
            break;
            case 't':
            case 'T':
            {
                if (object->canTalk())
                {
                    DebugConsole::debug_print (0, true, COLOR_CYAN, "\n\n%s talking.\n\n", object->GetName().c_str());
                    DebugConsole::debug_print (0, false, COLOR_WHITE, "%s\n\n", object->talk().c_str());
                }
            }
            break;
            case 'g':
            case 'G':
            {
                if (object->canTake() && !inPack)
                {
                    if (Player->MoveObjectToBackpack (object))
                    {
                        Controller->GetCurrentSpace()->RemoveObject (object);
                        commandObject = false;
                    }
                }
            }
            break;
            case 'u':
            case 'U':
            {
                // Generate list of objects to use.
                DebugConsole::debug_print (0, true, COLOR_CYAN, "\n\nSelect object to use %s on.\n\n", object->GetName().c_str());
                int maxObjectID = 0;
                int objectDivider = 0;
                for (int currentObject = 0; currentObject < NUM_ITEMS_INVENTORY; currentObject++)
                {
                    if (Player->GetBackpack()[currentObject] != __null)
                    {
                        DebugConsole::debug_print (0, false, COLOR_WHITE, "%d: %s\n", (maxObjectID++) + 1, Player->GetBackpack()[currentObject]->GetName().c_str());
                    }
                }
                objectDivider = maxObjectID;
                for (int currentObject = 0; currentObject < Controller->GetCurrentSpace()->GetObjects().size(); currentObject++)
                {
                    DebugConsole::debug_print (0, false, COLOR_WHITE, "%d: %s\n", (maxObjectID++) + 1, Controller->GetCurrentSpace()->GetObjects()[currentObject]->GetName().c_str());
                }
                DebugConsole::debug_print (0, false, COLOR_WHITE, "Enter item number >");
                std::string objectNumString = "";
                std::cin >> objectNumString;
                int objectNum = std::stoi(objectNumString);
                gameObject * target = __null;
                if ((objectNum > 0) && (objectNum <= maxObjectID))
                {
                    if (objectNum <= objectDivider)
                    {
                        // Object is in backpack.
                        target = Player->GetBackpack()[objectNum - 1];
                    }
                    else
                    {
                        // Object is in space.
                        objectNum -= objectDivider;
                        target = Controller->GetCurrentSpace()->GetObjects()[objectNum - 1];
                    }
                }
                else
                {
                    DebugConsole::debug_print (0, true, COLOR_YELLOW, "That is an invalid item.\n\n");
                    break;
                }
                if (target == __null)
                {
                    DebugConsole::debug_print (0, true, COLOR_YELLOW, "That is an invalid item.\n\n");
                    break;
                }
                if (!object->canUseItemOnTarget(target))
                {
                    DebugConsole::debug_print (0, true, COLOR_YELLOW, "\n\nUsing %s on %s...\n\n", object->GetName().c_str(), target->GetName().c_str());
                    DebugConsole::debug_print (0, true, COLOR_YELLOW, "That doesn't work...\n\n");
                    break;
                }
                else
                {
                    DebugConsole::debug_print (0, true, COLOR_GREEN, "Using %s on %s...\n\n", object->GetName().c_str(), target->GetName().c_str());
                    object->useItem(target);
                    Player->SortAndRecycleItems();
                    commandObject = false;
                    break;
                }
            }
            break;
        }
    }
}