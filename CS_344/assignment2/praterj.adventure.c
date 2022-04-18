///////////////////////////////////////////////////////
//
// CS 344 - Assignment 2 - Jeremy Prater
//
// Adventure Game!
//

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <pthread.h>

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

char gameDirectory[64];
room_t rooms[NUM_ROOMS];
room_t * startRoom;
room_t * endRoom;
room_t * currentRoom;
pthread_t timeThread;
pthread_mutex_t timeMutex = PTHREAD_MUTEX_INITIALIZER;
int timeThreadRunning = 1;
volatile int timerRunning = 0;

///////////////////////////////////////////////////////
//
// CheckTimeDiff returns true if the lhs time is
// greater than the rhs time, or false other wise.
//

int CheckTimeDiff (const struct timespec lhs, const struct timespec rhs)
{
    if (lhs.tv_sec == rhs.tv_sec)
        return lhs.tv_nsec > rhs.tv_nsec;
    else
        return lhs.tv_sec > rhs.tv_sec;
}

///////////////////////////////////////////////////////
//
// This returns the string of the newest directory
// that contains "pratej.rooms" based on st_mtim
//

char * FindNewestGameDir()
{
    // Open the current directory for reading all entries
    DIR * directoryScanner = opendir(".");
    struct dirent * currentDirectory;
    struct timespec newestDirectory;
    memset (&newestDirectory, 0, sizeof (newestDirectory));

    // Iterate while there while there are more entries
    while ((currentDirectory = readdir (directoryScanner)))
    {
        // Check if the entry is a directory and contains "praterj.rooms"
        if ((currentDirectory->d_type == DT_DIR) && (strstr(currentDirectory->d_name, "praterj.rooms") != NULL))
        {
            struct stat dirStat;
            stat (currentDirectory->d_name, &dirStat);
            // Check the time of the directory
            if (CheckTimeDiff(dirStat.st_mtim, newestDirectory))
            {
                // Save the newest directory
                strcpy(gameDirectory, currentDirectory->d_name);
                memcpy (&newestDirectory, &dirStat.st_mtim, sizeof (struct timespec));
            }
        }
    }
    printf ("Using game directory [%s]\n", gameDirectory);
    closedir (directoryScanner);
}

///////////////////////////////////////////////////////
//
// This Loads a room into the room[] array based on
// idex and a filename to load
//

void LoadRoom(int roomIndex, char * roomFileName)
{
    char localFileName[128];
    // Prepend the directory on the room filename
    snprintf(localFileName, 128, "%s/%s", gameDirectory, roomFileName);
    char localBuffer[128];
    printf ("Loading room [%s]\n", localFileName);
    // Open file for reading
    FILE * roomFile = fopen(localFileName, "r");
    if (roomFile == NULL)
    {
        printf ("Error Loading room [%s] [%s]\n", roomFileName, strerror(errno));
        exit(-2);
    }
    // Get the first line
    fgets(localBuffer, 128, roomFile);

    // Main line parsing loop
    do
    {
        localBuffer[strlen(localBuffer) - 1] = 0x00;
        if (strstr(localBuffer, "ROOM NAME"))
        {
            // The line is the ROOM NAME, store it in the destination
            char * token = strtok (localBuffer, ":");
            token = strtok (NULL, ":");
            token++;
            rooms[roomIndex].roomName = strdup(token);
            printf ("Room [%d] Name [%s]\n", roomIndex, rooms[roomIndex].roomName);
        }

        if (strstr(localBuffer, "CONNECTION"))
        {
            // The line is a connecion, store it in the destination
            char * token = strtok (localBuffer, " ");
            token = strtok (NULL, " ");
            token[1] = 0x00;
            int connectionIndex = atoi(token);
            token+=3;
            rooms[roomIndex].roomConnectionIDs[connectionIndex] = strdup(token);
            printf ("Room [%d] Connection [%d][%s]\n", roomIndex, connectionIndex, rooms[roomIndex].roomConnectionIDs[connectionIndex]);
        }


        if (strstr(localBuffer, "ROOM TYPE"))
        {
            // The line is the ROOM TYPE, store it in the destination
            char * token = strtok (localBuffer, ":");
            token = strtok (NULL, ":");
            token++;
            // Convert from a string into an enum.
            // Store the start and end rooms in global pointers
            if (strstr(token, "START_ROOM"))
            {
                rooms[roomIndex].roomType = ROOM_START;
                startRoom = &rooms[roomIndex];
                currentRoom = startRoom;
            }
            if (strstr(token, "MID_ROOM"))
            {
                rooms[roomIndex].roomType = ROOM_MID;
            }
            if (strstr(token, "END_ROOM"))
            {
                rooms[roomIndex].roomType = ROOM_END;
                endRoom = &rooms[roomIndex];
            }
            printf ("Room [%d] Type [%d]\n", roomIndex, rooms[roomIndex].roomType);
        }

        fgets(localBuffer, 128, roomFile);
    // Iterate through all liness
    } while (!feof(roomFile));
    fclose(roomFile);
}

///////////////////////////////////////////////////////
//
// Function to iterate through all room files.
//

void LoadGameData()
{
    // Open the game directory
    DIR * directoryScanner = opendir(gameDirectory);
    struct dirent * currentDirectory;
    int roomIndex = 0;
    // Loop through all items in the game directory
    while ((currentDirectory = readdir (directoryScanner)))
    {
        // If the file contains ".room" then load it.
        if (strstr(currentDirectory->d_name, ".room") != NULL)
        {
            // Load room
            LoadRoom (roomIndex++, currentDirectory->d_name);
        }
    }
    closedir (directoryScanner);
}

///////////////////////////////////////////////////////
//
// Find a pointer to a room based the string name
//

room_t * FindRoom(const char * name)
{
    int roomIndex = 0;
    for (roomIndex = 0; roomIndex < NUM_ROOMS; roomIndex++)
    {
        if (strcmp (name, rooms[roomIndex].roomName) == 0)
        {
            return &rooms[roomIndex];
        }
    }
    return NULL;    
}

///////////////////////////////////////////////////////
//
// Rooms are loaded and have strings that specify
// connections. Caching pointers to connections
// instead of string look ups will be easier to manage
//

void LinkRooms()
{
    int roomIndex = 0;
    // Loop through all rooms
    for (roomIndex = 0; roomIndex < NUM_ROOMS; roomIndex++)
    {
        room_t * currentRoom = &rooms[roomIndex];
        int connectionIndex = 0;
        // Loop through all connections in current room
        for (connectionIndex = 0; connectionIndex < NUM_CONNECTIONS; connectionIndex++)
        {
            // Check if there is a string in the current connection
            if (rooms[roomIndex].roomConnectionIDs[connectionIndex])
            {
                // Assign a pointer to the room in the look up array.
                rooms[roomIndex].roomConnections[connectionIndex] = (struct room_t *)FindRoom(rooms[roomIndex].roomConnectionIDs[connectionIndex]);
                
                // This all just debugging to help the user see which rooms are start/end
                printf ("Linking [%s]->[%s]", rooms[roomIndex].roomName, ((room_t *)rooms[roomIndex].roomConnections[connectionIndex])->roomName);
                if (rooms[roomIndex].roomType == ROOM_START)
                {
                    printf (" ---> [START]");
                }
                if (rooms[roomIndex].roomType == ROOM_END)
                {
                    printf (" <--- [END]");
                }
                printf ("\n");
            }
        }
    }
}

///////////////////////////////////////////////////////
//
// This is the game running loop
//

int runGame()
{
    // Print current location
    printf ("CURRENT LOCATION: %s\n", currentRoom->roomName);

    char roomConnections[512];
    char userInput[128];
    memset (roomConnections, 512, 0);
    char * roomConnectionStringPtr = roomConnections;
    int connectionIndex = 0;
    // Loop through all connections
    for (connectionIndex = 0; connectionIndex < NUM_CONNECTIONS; connectionIndex++)
    {
        // Check if the connection is a pointer to another room
        if (currentRoom->roomConnections[connectionIndex])
        {
            // Copy the rooms name to the current string.
            // memcpy was a better choice than strcpy because I do not
            // want to append the terminating null character now.
            // This also adds comma ',' and spaces ' '
            const char * connectorName = ((room_t *)currentRoom->roomConnections[connectionIndex])->roomName;
            int stringLength = strlen(connectorName);
            memcpy (roomConnectionStringPtr, connectorName, stringLength);
            roomConnectionStringPtr += stringLength;
            *roomConnectionStringPtr = ',';
            roomConnectionStringPtr++;
            *roomConnectionStringPtr = ' ';
            roomConnectionStringPtr++;
        }
    }
    // Back up two characters
    roomConnectionStringPtr--;
    roomConnectionStringPtr--;
    // Terminate the string
    *roomConnectionStringPtr = '.';
    roomConnectionStringPtr++;
    *roomConnectionStringPtr = 0x00;
    // Print the connections
    printf ("POSSIBLE CONNECTIONS: %s\n", roomConnections);
    printf ("WHERE TO? >");

    // Get user input
    fgets(userInput, 128, stdin);
    userInput[strlen(userInput) - 1] = 0x00;

    int foundRoom = 0;

    // Check if we are executing the time command
    if (strcmp (userInput, "time") == 0)
    {
        // Set the timer running flag
        timerRunning = 1;
        // Unlock the mutex
        pthread_mutex_unlock (&timeMutex);

        // Wait here until a context switch occurs into the timer thread
        // This works becuase timerRunning is a volatile variable
        while (timerRunning);

        // Lock timer mutex
        pthread_mutex_lock (&timeMutex);
        return 0;
    }
    else
    {
        // We are going to a room.
        int connectionIndex = 0;
        // Iterate through all connections
        for (connectionIndex = 0; connectionIndex < NUM_CONNECTIONS; connectionIndex++)
        {
            if (currentRoom->roomConnections[connectionIndex])
            {
                if (strcmp (userInput, ((room_t *)currentRoom->roomConnections[connectionIndex])->roomName) == 0)
                {
                    // We found a connection to a new room.
                    // Move to that room
                    currentRoom = (room_t *)currentRoom->roomConnections[connectionIndex];
                    foundRoom = 1;
                }
            }
        }
    }

    // No room was found with that name, so print the error message.
    if (!foundRoom)
    {
        printf ("\nHUH? I DON’T UNDERSTAND THAT ROOM. TRY AGAIN.\n");
        return 0;
    }

    printf ("\n");

    return 1;
}

///////////////////////////////////////////////////////
//
// This is the timer running loop
//

void * timeFunction(void * context)
{
    // Time thread runs while the main thread is running
    while (timeThreadRunning)
    {
        // We wait for the mutex to unlock
        pthread_mutex_lock (&timeMutex);

        // Check if the timer is still alive.
        // This is the exit case, where we set timerThreadRunning to false
        // and unlock the mutex, which kills the thread
        // timerRunning is a flag to control what the timer is doing
        // timeMutex protects access to the timerRunning variable and controls
        // thread execution.

        if (timeThreadRunning && timerRunning)
        {
            // Print the time and save it to a file called currentTime.txt
            // timerRunning allows the main thread to continue when the mutex is unlocked.
            timerRunning = 0;
            time_t now;
            time (&now);
            const struct tm * timeNow = localtime (&now);
            char timeString[128];
            memset (timeString, 0, 128);
            strftime(timeString, 128, "%l:%M%p, %A, %B %d, %Y", timeNow);
            printf ( "\n %s\n\n", timeString);
            FILE * timeFile = fopen ("currentTime.txt", "w");
            if (!timeFile)
            {
                printf ("Failed to create currentTime.txt [%s]", strerror(errno));
                exit (-4);
            }
            timeString[strlen(timeString)] = '\n';
            fwrite(timeString, strlen (timeString), 1, timeFile);
            fclose (timeFile);
          
        }
        // Unlock the mutex and return to main thread.
        pthread_mutex_unlock (&timeMutex);
    }
}

///////////////////////////////////////////////////////
//
// Main program entry point
//

int main(int argc, char * argv[])
{
    // Create the timer thread
    // Lock the timer mutex when program execution begins
    pthread_mutex_lock (&timeMutex);
    if (pthread_create(&timeThread, NULL, timeFunction, NULL))
    {
        printf ("Failed to create time worker thread!\n");
        exit (-3);
    }
    // Initalize program memory
    memset (gameDirectory, 0, sizeof (gameDirectory));
    memset (rooms, 0, sizeof(room_t) * NUM_ROOMS);
    
    // Find the game directory
    FindNewestGameDir();
    if (strlen(gameDirectory) == 0)
    {
        // Print an error and exit if no rooms are found
        printf("No valid game directories found! run praterj.buildsrooms first\n");
        return -1;
    }
    
    // Load game rooms and create pointer links
    LoadGameData();
    LinkRooms();
    printf ("\n");
    printf ("------------------------------------------------------------------------\n");
    printf ("|  CS 344 Adventure game                                               |\n");
    printf ("|                                                                      |\n");
    printf ("|  Jeremy Prater                                                       |\n");
    printf ("|  praterj@oregonstate.edu                                             |\n");
    printf ("|  https://github.com/jeremy-prater/OSU/tree/master/CS_344/assignment2 |\n");
    printf ("|                                                                      |\n");
    printf ("------------------------------------------------------------------------\n");
    printf ("\n");
    
    // Setup the history array and turn counter
    int turnCounter = 0;
    char ** history = (char**)malloc(sizeof (char*));
    
    // Main game loop
    while (currentRoom != endRoom)
    {
        // Get the status of the turn. true means the turn was successful (ie. a move occured)
        int turnStatus = runGame();
        if (turnStatus)
        {
            history = (char**)realloc (history, sizeof (char*) * (turnCounter + 1));
            history[turnCounter] = strdup(currentRoom->roomName);
        }
        turnCounter += turnStatus;
    }

    // The game is over because the current room is the end room
    
    // Print game stats and history
    printf ("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
    printf ("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", turnCounter);
    int historyIndex = 0;
    for (historyIndex = 0; historyIndex < turnCounter; historyIndex++)
    {
        printf("%s\n", history[historyIndex]);
        free (history[historyIndex]);
    }

    // Clean up any dyamically allocated memory
    free (history);
    int roomIndex = 0;
    for (roomIndex = 0; roomIndex < NUM_ROOMS; roomIndex++)
    {
        free ((void*)rooms[roomIndex].roomName);
        int connectionIndex = 0;
        for (connectionIndex = 0; connectionIndex < NUM_CONNECTIONS; connectionIndex++)
        {
            if (((room_t*)&rooms[roomIndex])->roomConnectionIDs[connectionIndex])
            {
                free ((void*)((room_t*)&rooms[roomIndex])->roomConnectionIDs[connectionIndex]);
            }
        }
    }
    
    // Shutdown the timer thread
    timeThreadRunning = 0;
    pthread_mutex_unlock (&timeMutex);
    pthread_join(timeThread, NULL);
    
    // We're outta here!
    return 0;
}
