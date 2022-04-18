/*********************************************************************
** Author:       Jeremy Prater
** Date:         August 1, 2016
** Description:  gameObjects.cpp
*********************************************************************/

#include "gameObjects.hpp"
#include "gamePlayer.hpp"
#include "gameSpaceController.hpp"
#include "lib_flip_display.hpp"

////////////////////////////////////////////////////////////////////////////////////////////
//
// objectTypes ...::GetObjectType()
//
// Return the type of the object from derived classes
//

objectTypes gameObjectKnife::GetObjectType() { return objectTypeKnife; }
objectTypes gameObjectChest::GetObjectType() { return objectTypeChest; }
objectTypes gameObjectLock::GetObjectType() { return objectTypeLock; }
objectTypes gameObjectCrystalOrb::GetObjectType() { return objectTypeCrystalOrb; }
objectTypes gameObjectFlower::GetObjectType() { return objectTypeFlower; }
objectTypes gameObjectTeaPot::GetObjectType() { return objectTypeTeaPot; }
objectTypes gameObjectElixer::GetObjectType() { return objectTypeElixer; }
objectTypes gameObjectStarFish::GetObjectType() { return objectTypeStarFish; }
objectTypes gameObjectSquirtle::GetObjectType() { return objectTypeSquirtle; }
objectTypes gameObjectStarmie::GetObjectType() { return objectTypeStarmie; }
objectTypes gameObjectGem::GetObjectType() { return objectTypeGem; }
objectTypes gameObjectGemKey::GetObjectType() { return objectTypeGemKey; }
objectTypes gameObjectOrbHole::GetObjectType() { return objectTypeOrbHole; }
objectTypes gameObjectStick::GetObjectType() { return objectTypeStick; }
objectTypes gameObjectLantern::GetObjectType() { return objectTypeLantern; }
objectTypes gameObjectMagicDoor::GetObjectType() { return objectTypeMagicDoor; }

////////////////////////////////////////////////////////////////////////////////////////////
//
// std::string ...::GetName()
//
// Return the name of the object from derived classes
//

std::string gameObjectKnife::GetName() { return "Knife"; }
std::string gameObjectChest::GetName() { return "Chest"; }
std::string gameObjectLock::GetName() { return "Lock"; }
std::string gameObjectCrystalOrb::GetName() { return "Crystal Orb"; }
std::string gameObjectFlower::GetName() { return "Flowers"; }
std::string gameObjectTeaPot::GetName() { return "Teapot"; }
std::string gameObjectElixer::GetName() { return "Elixer"; }
std::string gameObjectStarFish::GetName() { return "StarFish"; }
std::string gameObjectSquirtle::GetName() { return "Squirtle"; }
std::string gameObjectStarmie::GetName() { return "Starmie"; }
std::string gameObjectGem::GetName() { return "Gem"; }
std::string gameObjectGemKey::GetName() { return "Gem Key"; }
std::string gameObjectOrbHole::GetName() { return "Orb Holder"; }
std::string gameObjectStick::GetName() { return "Stick"; }
std::string gameObjectLantern::GetName() { return "Lantern"; }
std::string gameObjectMagicDoor::GetName() { return "Magic Door"; }

////////////////////////////////////////////////////////////////////////////////////////////
//
// bool ...::canUseItemOnTarget(gameObject * object)
//
// Return true if a object can be used on another object for derived classes
//

bool gameObjectKnife::canUseItemOnTarget(gameObject * object)
{
    // Knife can be used on Gem and Lock
    return ((object->GetObjectType() == objectTypeGem) || (object->GetObjectType() == objectTypeLock) || (object->GetObjectType() == objectTypeChest));

}
bool gameObjectCrystalOrb::canUseItemOnTarget(gameObject * object)
{
    // Orb can be used on OrbHole
    return (object->GetObjectType() == objectTypeOrbHole);
}
bool gameObjectFlower::canUseItemOnTarget(gameObject * object)
{
    // Flower can be used on Teapot
    return (object->GetObjectType() == objectTypeTeaPot);
} 
bool gameObjectElixer::canUseItemOnTarget(gameObject * object)
{
    // Elixer can be used on Starfish
    return (object->GetObjectType() == objectTypeStarFish);
}
bool gameObjectGemKey::canUseItemOnTarget(gameObject * object)
{
    // GemKey can be used on MagicDoor
    gameObjectOrbHole * orbHole = (gameObjectOrbHole *)Controller->GetGameSpaceByType(gameSpaceLocationCave)->GetObject(objectTypeOrbHole);
    if (!orbHole->HasOrb())
    {
        DebugConsole::debug_print (0, true, COLOR_YELLOW, "\n\nThe door doesn't seem to accept the key...\n\n");
        return false;
    }
    return (object->GetObjectType() == objectTypeMagicDoor);
}
bool gameObjectStick::canUseItemOnTarget(gameObject * object)
{
    // Stick can be used on Lantern
    return (object->GetObjectType() == objectTypeLantern);
}

////////////////////////////////////////////////////////////////////////////////////////////
//
// void ...::useItem(gameObject * target)
//
// Logic for object to object interactions.
//

void gameObjectFlower::useItem(gameObject * object)
{
    // This can only be called if object->GetType() == objectTypeTeapot
    DebugConsole::debug_print (0, true, COLOR_GREEN, "\n\nThe flowers slowly boil down into a sparkling thick liquid with a sweet smell.\n\n");
    Controller->GetPlayer()->CreateObjectInBackpack(objectTypeElixer);
    // Delete this object somehow...
    Controller->GetPlayer()->DestroyObjectInBackpack (this);
}

void gameObjectKnife::useItem(gameObject * object)
{
    if (object->GetObjectType() == objectTypeLock)
    {
        DebugConsole::debug_print (0, true, COLOR_GREEN, "\n\nYou jam the knife into the lock tumbler and the springs snap.\nThe lock is free to rotate.\nYou remove the lock and set it aside.\nYou remove the latch to the basement door.\n\n");
        gameObjectLock * lock = (gameObjectLock *)object;
        lock->BreakLock();
    }
    if (object->GetObjectType() == objectTypeChest)
    {
        DebugConsole::debug_print (0, true, COLOR_GREEN, "\n\nYou jam the knife between the lid of the chest near the latch and push.\nThe rusty metal snaps easily.\nYou open the chest and see a crystal orb.\n\n");
        Controller->GetCurrentSpace()->CreateObject(objectTypeCrystalOrb);
        gameObjectChest * chest = (gameObjectChest *) object;
        chest->OpenChest();
    }
    if (object->GetObjectType() == objectTypeGem)
    {
        DebugConsole::debug_print (0, true, COLOR_GREEN, "\n\nYou use the knife to scrape some of the Gem away and it slides apart.\nInside is a hexagonal stone that looks like a key.\n\n");
        Controller->GetPlayer()->DestroyObjectInBackpack(object);
        Controller->GetPlayer()->CreateObjectInBackpack(objectTypeGemKey);
    }
}

void gameObjectElixer::useItem(gameObject * object)
{
    // This can be only used on Starfish
    DebugConsole::debug_print (0, true, COLOR_GREEN, "\n\nYou pour the elixer on the star fish...\n\nIt starts changing into something else.\n\n");
    Controller->GetCurrentSpace()->DestroyObject(object);
    Controller->GetCurrentSpace()->CreateObject(objectTypeStarmie);
    Controller->GetPlayer()->DestroyObjectInBackpack(this);
}

void gameObjectStick::useItem(gameObject * object)
{
    // This can be only used on lantern
    DebugConsole::debug_print (0, true, COLOR_GREEN, "\n\nYou put the stick inside of the lantern and light it on fire.\nThe latern glows brightly.\n\n");
    gameObjectLantern * lantern = (gameObjectLantern *) object;
    lantern->SetStick();
    Controller->GetPlayer()->DestroyObjectInBackpack(this);
}

void gameObjectCrystalOrb::useItem (gameObject * object)
{
    // This can be only used on Orb Holder
    DebugConsole::debug_print (0, true, COLOR_GREEN, "\n\nYou put the orb near the orb holder.\nThe orb is slowly drawn in by some type of force.\nThe orb fits fully inside of the orb holder and the symbols around the holder begin to glow.\n\n");
    gameObjectOrbHole * orbHole = (gameObjectOrbHole *) object;
    orbHole->SetOrb();
    Controller->GetPlayer()->DestroyObjectInBackpack(this);
}

void gameObjectGemKey::useItem (gameObject * object)
{
    // This can be only used on the magic door
    DebugConsole::debug_print (0, true, COLOR_GREEN, "\n\nYou put the key into the door.\nThe door hisses with air releasing as it unseals.\n\n");
    gameObjectMagicDoor * magicDoor = (gameObjectMagicDoor *) object;
    magicDoor->SetKey();
    Controller->GetPlayer()->DestroyObjectInBackpack(this);
}


////////////////////////////////////////////////////////////////////////////////////////////
//
// std::string ...::GetText()
//
// Return the text describing an object for derived classes
//

std::string gameObjectKnife::GetText() { return "A rusty old knife with an intricate wooden handle.\n\nEngraved on the handle are the letters \"JP\"\n\n"; }
std::string gameObjectChest::GetText()
{
    if (chestOpened)
    {
        return "An opened chest.\n\nThe inside is padded with cloth and foam.\n\n";
    }
    else
    {
        return "A locked Chest.\n\nThe lock looks very weak and old.\n\n";
    }
}
std::string gameObjectLock::GetText()
{
    if (lockBroken)
    {
        return "A broken old lock.\n\nThe tumbler is broken and can spin freely.\n\n";
    }
    else
    {
        return "An old lock.\n\nThe tumbler looks intact.\n\n";
    }
}
std::string gameObjectCrystalOrb::GetText() { return "A small glowing crystal orb.\n\nIt appears to emit a type of blue light.\n\n"; }
std::string gameObjectFlower::GetText() { return "A group of small orange flowers with many pedals.\n\n"; }
std::string gameObjectTeaPot::GetText() { return "A Teapot\n\n"; }
std::string gameObjectElixer::GetText() { return "The elixer brewed from orange flowers.\n\n"; }
std::string gameObjectStarFish::GetText() { return "A Starfish covered in some type of goo.\n\nIt looks sick.\n\n"; }
std::string gameObjectSquirtle::GetText()
{
    if (Controller->GetGameSpaceByType(gameSpaceLocationRiver)->ContainsObject(objectTypeStarmie) == true)
    {
        return "A Squirtle (some type of turtle).\n\nIt appears to be happy.\n\n";
    }
    else
    {
        return "A Squirtle (some type of turtle).\n\nIt appears to be sad.\n\n";
    }
}
std::string gameObjectStarmie::GetText() { return "A happy Starmie.\n\nIt is swimming back and forth.\n\n"; }
std::string gameObjectGem::GetText() { return "A glowing green gem.\n\nIt appears to slide apart and something is inside.\n\n"; }
std::string gameObjectGemKey::GetText() { return "A key from the green gem.\n\n"; }
std::string gameObjectOrbHole::GetText()
{
    if (hasOrb)
    {
        return "A small hole in the wall that has a blue orb in it.\n\nThere are symbols around the hole that are glowing brightly.\n\n";
    }
    else
    {
        return "A small hole in the wall that has a slight blue glow.\n\nThere are symbols around the hole.\n\n";
    }
}
std::string gameObjectStick::GetText() { return "A dried out old stick.\n\nPerfect for burning.\n\n"; }
std::string gameObjectLantern::GetText()
{
    if (hasStick)
    {
        return "An old lantern.\n\nThere is an old stick inside of it burning.\n\n";
    }
    else
    {
        return "An old lantern.\n\nIt does not have any thing to burn inside of it.\n\n";
    }
    
}
std::string gameObjectMagicDoor::GetText()
{
    if (doorKey)
    {
        return "A magic door with the gem in the key hole.\n\nThe center of the door became transparent and looks like running water.";
    }
    else
    {
        return "A magic door with an empty key hole.\n\n";
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
//
// bool ...::canTake()
//
// Return true if an object can be placed in the backpack for derived classes
//

bool gameObjectStick::canTake() { return true; }
bool gameObjectFlower::canTake() { return true; }
bool gameObjectCrystalOrb::canTake() { return true; }
bool gameObjectGem::canTake() { return true; }
bool gameObjectKnife::canTake() { return true; }
bool gameObjectElixer::canTake() { return true; }
bool gameObjectLantern::canTake() { return true; }


////////////////////////////////////////////////////////////////////////////////////////////
//
// bool ...::canTalk ()
// std::string ...::talk()
//
// Return true if an object can talk and the text string for derived classes
//

bool gameObjectStarFish::canTalk () { return true; }
std::string gameObjectStarFish::talk()
{
    return "\nBLURRB... BLURRBBB....\n\nI am very sick.\n\nSomeone is poisoning the creatures of this land.\n\nHelp us... BLURBB.. BLURB..\n\n";
}

bool gameObjectStarmie::canTalk () { return true; }
std::string gameObjectStarmie::talk()
{
    return "Thank you so much!\n\nI have been transformed into a stronger creature!";
}

bool gameObjectSquirtle::canTalk () { return true; }
std::string gameObjectSquirtle::talk()
{
    static bool firstTime = true;
    static bool rewarded = false;
    if (Controller->GetGameSpaceByType(gameSpaceLocationRiver)->ContainsObject(objectTypeStarFish))
    {
        if (firstTime == true)
        {
            firstTime = false;
            return "\t\tHello traveler...\n\n\tI have a gift for you, but first you need to help my friend. There is a pond a short walk from here.\nMy friend that lives in it is sick and needs the brewed elixer from flowers that grow in this area to heal.\n\nPlease help him and I will reward you!\n\n";
        }
        else
        {
            return "\tHave you found my friend?\n\nIt makes me sad that he is still stick.\nThe flowers that grow in this area will cure him if they are brewed.";
        }
    }
    else
    {
        if (rewarded == false)
        {
            // Give reward.
            rewarded = true;
            Controller->GetPlayer()->CreateObjectInBackpack(objectTypeGem);
            return "\t\tMy friend is healed! Thank you so much!\n\tHere is a specal gem that I have been saving. I think it came from a nearby cave.";        }
        else
        {
            // Thanks
            return "Thanks again!";
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
//
// void gameObjectOrbHole::SetOrb()
// bool gameObjectOrbHole::HasOrb()
//
// Logic for controlling the Orb holder in the cave.
//

void gameObjectOrbHole::SetOrb()
{
    hasOrb = true;
}

bool gameObjectOrbHole::HasOrb()
{
    return hasOrb;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
// void gameObjectLock::BreakLock()
// bool gameObjectLock::GetLockBroken()
//
// Logic for controlling the lock in the cabin.
//

void gameObjectLock::BreakLock()
{
    lockBroken = true;
}

bool gameObjectLock::GetLockBroken()
{
    return lockBroken;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
// void gameObjectLantern::SetStick()
// bool gameObjectLantern::HasStick()
//
// Logic for controlling the stick and lantern.
//

void gameObjectLantern::SetStick()
{
    hasStick = true;
}

bool gameObjectLantern::HasStick()
{
    return hasStick;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
// void gameObjectMagicDoor::SetKey()
// bool gameObjectMagicDoor::HasKey()
//
// Logic for controlling the MagicDoor and Key
//

void gameObjectMagicDoor::SetKey()
{
    doorKey = true;
}
bool gameObjectMagicDoor::HasKey()
{
    return doorKey;
}

////////////////////////////////////////////////////////////////////////////////////////////
//
// void gameObjectChest::OpenChest();
// bool gameObjectChest::GetChestOpen();
//
// Logic for controlling the lockedchest
//

void gameObjectChest::OpenChest()
{
    chestOpened = true;
}

bool gameObjectChest::GetChestOpen()
{
    return chestOpened;
}
