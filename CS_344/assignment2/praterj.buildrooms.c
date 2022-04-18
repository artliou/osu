///////////////////////////////////////////////////////
//
// CS 344 - Assignment 2 - Jeremy Prater
//
// Build Rooms
//

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
///////////////////////////////////////////////////////
//
// Definitions for program configuration
//

#define NUM_ROOMS 7
#define MAX_ROOMS 10
#define NUM_CONNECTIONS 6
#define NUM_DEFAULT_CONNECTIONS 3
#define MAX_ROOM_PATH 256

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

///////////////////////////////////////////////////////
//
// Enumerations
//

typedef enum
{
    ROOM_START = 1,
    ROOM_MID = 2,
    ROOM_END = 3
} ROOM_TYPE;

///////////////////////////////////////////////////////
//
// Room data structure
//

typedef struct
{
    const char * roomName;
    char roomFile[MAX_ROOM_PATH];
    struct room_t * roomConnections[NUM_CONNECTIONS];
    const char * roomConnectionIDs[NUM_CONNECTIONS];
    int roomCreated;
    int roomChecked;
    int numConnections;
    ROOM_TYPE roomType;
} room_t;

///////////////////////////////////////////////////////
//
// Global variables...
//
// This should be avoided, but given the scope of the
// scope of the program, this is the easiest way.
//

static const char * roomNames[MAX_ROOMS] = {
    "Great Hall",
    "Workshop",
    "Kitchen",
    "Blacksmith",
    "Kitchen",
    "Bathroom",
    "Game room",
    "Garage",
    "Basement",
    "Garden"
};

static room_t roomData[NUM_ROOMS];
static room_t * startRoom = 0;
static room_t * endRoom = 0;
static int totalLinks = 0;

///////////////////////////////////////////////////////
//
// Create room names, in a random order
//
// A room may be created only once
//

void CreateRooms(room_t * rooms)
{
    // Seed the PRNG with the system time
    srand (time(NULL));

    // Initalize room data
    memset (roomData, 0, sizeof (roomData));
    
    // Iterate until the correct number of rooms have been created
    int roomCreationCount = 0;
    while (roomCreationCount < NUM_ROOMS)
    {
        // Find a new room index
        int newRoomIndex = -1;
        while (newRoomIndex == -1)
        {
            newRoomIndex = rand() % MAX_ROOMS;
            // Check if room is already used...
            int checkIndex = 0;
            for (checkIndex = 0; checkIndex < NUM_ROOMS; checkIndex++)
            {
                if (rooms[checkIndex].roomCreated)
                {
                    if (strcmp (rooms[checkIndex].roomName, roomNames[newRoomIndex]) == 0)
                    {
                        // Uh, oh. That room is already created. Try again
                        newRoomIndex = -1;
                        break;
                    }
                }
            }
        }

        // Check if that room has already been created (this should be redundant)
        if (rooms[roomCreationCount].roomCreated)
        {
            continue;
        }
        else
        {
            // Assign room data to the structure in memory
            rooms[roomCreationCount].roomName = roomNames[newRoomIndex];
            snprintf (rooms[roomCreationCount].roomFile, MAX_ROOM_PATH, "%s.room", rooms[roomCreationCount].roomName);
            printf ("Created room [%s] with file name [%s]\n", rooms[roomCreationCount].roomName, rooms[roomCreationCount].roomFile);
            rooms[roomCreationCount].roomCreated = 1;
            rooms[roomCreationCount].roomType = ROOM_MID;
            roomCreationCount++;
        }
    }
    // Pick the start and end rooms
    int startRoomIndex = rand() % NUM_ROOMS;
    int endRoomIndex = startRoomIndex;

    // Ensure that the start and end rooms are not equal
    while (endRoomIndex == startRoomIndex)
    {
        endRoomIndex = rand() % NUM_ROOMS;
    }

    // Final setup
    startRoom = &rooms[startRoomIndex];
    endRoom = &rooms[endRoomIndex];
    startRoom->roomType = ROOM_START;
    endRoom->roomType = ROOM_END;
}

///////////////////////////////////////////////////////
//
// Find the next empty connection slot for a given room
//

int FindEmptyRoomSlot(room_t * room)
{
    int connectionIndex = 0;
    for (connectionIndex = 0; connectionIndex < NUM_CONNECTIONS; connectionIndex++)
    {
        if (!room->roomConnections[connectionIndex])
        {
            return connectionIndex;
        }
    }
    return -1;
}

///////////////////////////////////////////////////////
//
// Attempt to create a link between too rooms by index
//
// Returns 1 for success
// Returns 0 for failed to create link
//

int CreateLink(room_t * rooms, int A, int B)
{
    // If rooms are equal, fail
    if (A == B)
    {
        return 0;
    }

    // Iterate through all connections in A and B to check if they are already connected
    int testRoomIndexA = 0;
    for (testRoomIndexA = 0; testRoomIndexA < NUM_CONNECTIONS; testRoomIndexA++)
    {
        int testRoomIndexB = 0;
        for (testRoomIndexB = 0; testRoomIndexB < NUM_CONNECTIONS; testRoomIndexB++)
        {
            // Check if room B is already connected to room A
            if (
                (rooms[A].roomConnections[testRoomIndexA]) &&
                (rooms[B].roomConnections[testRoomIndexB]) &&
                (
                    (rooms[A].roomConnections[testRoomIndexA] == (struct room_t *)&rooms[B]) ||
                    (rooms[B].roomConnections[testRoomIndexB] == (struct room_t *)&rooms[A])
                ))
            {
                // No good, the rooms are already connected...
                return 0;
            }
        }
    }
    // Find empty slot and connect rooms
    int aIndex = FindEmptyRoomSlot(&rooms[A]);
    int bIndex = FindEmptyRoomSlot(&rooms[B]);
    rooms[A].roomConnections[aIndex] = (struct room_t*)&rooms[B];
    rooms[B].roomConnections[bIndex] = (struct room_t*)&rooms[A];
    rooms[A].numConnections++;
    rooms[B].numConnections++;
    printf ("Connecting [%s] to [%s] [%p]=[%p]\n",
        rooms[A].roomName,
        rooms[B].roomName,
        rooms[A].roomConnections[aIndex],
        rooms[B].roomConnections[bIndex]);

    // Increment the total link counter
    totalLinks++;
    return 1;
}

///////////////////////////////////////////////////////
//
// Link random rooms together
//
// All rooms must have at LEAST 3 connections
// No duplicate connections are allowed
//

void LinkRooms(room_t * rooms)
{
    // status variable to determine if we have met exit conditions
    int linking = 1;
    while (linking)
    {
        // minLinks is the variable that is the MINIMUM number of links for all rooms this round
        int minLinks = NUM_ROOMS;
        int roomIndex = 0;
        // Iterate through all rooms
        for (roomIndex = 0; roomIndex < NUM_ROOMS; roomIndex++)
        {
            // Generate a connecting room index
            int A = roomIndex;
            int B = -1;
            int searching = 1;
            B = rand() % NUM_ROOMS;
            if (B != A)
            {
                // No rooms connect to self
                if (CreateLink(rooms, A, B))
                {
                    // If the link was successful then get the minimum number of connections
                    minLinks = MIN(minLinks, rooms[A].numConnections);
                    minLinks = MIN(minLinks, rooms[B].numConnections);
                }
            }
        }
        // If we have 3 or more connections for ALL rooms, then exit.
        if (minLinks >= 3)
        {
            linking = 0;
        }
    }
}

///////////////////////////////////////////////////////
//
// Check that there is a path from start->end
//
// This is a recursive depth-first search
//

int CheckConnectivity(room_t * start, room_t * end)
{
    // Recurisive functions! Yay!

    // Flag that we have already checked this path
    // There is a posiblity that a circular graph could be created
    // This causes an infinite loop
    start->roomChecked = 1;
    
    if (start == end)
    {
        // We found the end!
        return 1;
    }

    // Loop over all room connections
    int foundIt = 0;
    int roomIndex = 0;
    for (roomIndex = 0; roomIndex < NUM_CONNECTIONS; roomIndex++)
    {
        // If there is no connection in this index, then skip it
        if (!(room_t*)start->roomConnections[roomIndex])
        {
            continue;
        }

        // If the connecting room has not yet been checked...
        if (!((room_t*)start->roomConnections[roomIndex])->roomChecked)
        {
            // Logically OR the result from this function with all other connections
            // in this room, recursively...
            foundIt |= CheckConnectivity((room_t*)start->roomConnections[roomIndex], end);
        }
    }

    // Return the recursive search result
    return foundIt;
}

///////////////////////////////////////////////////////
//
// Save an individual room to the filesystem
//

void SaveRoom(room_t * room)
{
    // Open the output file
    printf ("Saving file [%s]\n", room->roomFile);
    FILE * outFile = fopen(room->roomFile, "w");
    
    // Write the ROOM NAME
    fprintf (outFile, "ROOM NAME: %s\n", room->roomName);
    
    // Write all connections
    int connectionIndex = 0;
    for (connectionIndex = 0; connectionIndex < NUM_CONNECTIONS; connectionIndex++)
    {
        if (room->roomConnections[connectionIndex])
        {
            fprintf (outFile, "CONNECTION %d: %s\n", connectionIndex + 1, ((room_t*)room->roomConnections[connectionIndex])->roomName);
        }
    }

    // Write the ROOM TYPE
    switch (room->roomType)
    {
        case ROOM_START:
        fprintf (outFile, "ROOM TYPE: START_ROOM\n");
        break;
        case ROOM_MID:
        fprintf (outFile, "ROOM TYPE: MID_ROOM\n");
        break;
        case ROOM_END:
        fprintf (outFile, "ROOM TYPE: END_ROOM\n");
        break;
    }
    
    // Close the file
    fclose(outFile);
}

///////////////////////////////////////////////////////
//
// Save room data to the filesystem
//

void SaveRooms(room_t * rooms)
{
    // Create the output directory
    char directory[64];
    snprintf (directory, MAX_ROOM_PATH, "./praterj.rooms.%d", getpid());
    mkdir(directory, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    
    // Enter the output directory
    chdir (directory);

    // Loop over each room and save it to the drive
    int roomIndex = 0;
    for (roomIndex = 0; roomIndex < NUM_ROOMS; roomIndex++)
    {
        SaveRoom (&rooms[roomIndex]);
    }
    
    // Return to the parent directory
    chdir ("..");
    printf ("Game data saved in [%s]\n", directory);
}

///////////////////////////////////////////////////////
//
// Main program entry point
//

int main(int argc, char * argv[])
{
    // Create the array of room names
    CreateRooms(roomData);

    // Randomly link rooms
    LinkRooms (roomData);

    // Check that there is a path from start->end
    while (!CheckConnectivity(startRoom, endRoom))
    {
        // Randomly add a link in hopes that a path is created
        // from start->end
        CreateLink(roomData, rand() % NUM_ROOMS, rand() % NUM_ROOMS);
    }

    // Print the total number of room connections
    printf ("Total room connections [%d]\n", totalLinks);
    
    // Save the room data to the filesystem.
    SaveRooms (roomData);

    // We're outta here!
    return 0;
}
