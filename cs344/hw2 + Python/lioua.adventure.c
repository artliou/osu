/***
* Arthur Liou
* CS 344 Assignment 2
* Adventure Game
* Notes on Comments. I thought most of the code is relatively self explanation, so 
* I just only have a small blurb at the top of section that described what it did.
& If the comeents isn't enough, please let me know & I can submit a revised version of this file
***/ 

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <dirent.h>
#include <pthread.h>

// Program Definitions
#define NUM_ROOMS 7
#define MAX_ROOMS 10
#define NUM_CONNECTIONS 6
#define NUM_DEFAULT_CONNECTIONS 3
#define MAX_ROOM_PATH 256
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

// Enumerations
typedef enum
{
    ROOM_START = 1,
    ROOM_MID = 2,
    ROOM_END = 3
} ROOM_TYPE;

// Room - Structure
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

// Global environment variables
char gameDirectory[64];
room_t rooms[NUM_ROOMS];
room_t * startRoom;
room_t * endRoom;
room_t * currRoom;
pthread_t timeThread;
pthread_mutex_t timeMutex = PTHREAD_MUTEX_INITIALIZER;
int timeThreadRunning = 1;
volatile int timerTicking = 0;

// checkTimeDifference returns true if the left time is
// greater than the right time, or false other wise.
int checkTimeDifference (const struct timespec left, const struct timespec right)
{
    if (left.tv_sec == right.tv_sec)
        return left.tv_nsec > right.tv_nsec;
    else
        return left.tv_sec > right.tv_sec;
}

// This returns the string of the newest directory that contains "lioua.rooms" based on time
char * findNewGameDirectory()
{
    // Open the curr dir
    DIR * directoryScanner = opendir(".");
    struct dirent * currDirectory;
    struct timespec newDirectory;
    memset (&newDirectory, 0, sizeof(newDirectory));

    // Iterate while there while there are more entries
    while ((currDirectory = readdir(directoryScanner)))
    {
        // Check if the entry is a directory and contains "lioua.rooms"
        if ((currDirectory->d_type == DT_DIR) && (strstr(currDirectory->d_name, "lioua.rooms") != NULL))
        {
            struct stat directoryStatus;
            stat(currDirectory->d_name, &directoryStatus);
            // Check the time of the directory
            if (checkTimeDifference(directoryStatus.st_mtim, newDirectory))
            {
                // Save the newest directory
                strcpy(gameDirectory, currDirectory->d_name);
                memcpy (&newDirectory, &directoryStatus.st_mtim, sizeof (struct timespec));
            }
        }
    }
    printf("Using game directory [%s]\n", gameDirectory);
    closedir(directoryScanner);
}

// Loads a single room into the room array
void loadRoom(int roomIndex, char * roomFileName)
{
    // Prepend the directory on the room filename
    char localFileName[128];
    snprintf(localFileName, 128, "%s/%s", gameDirectory, roomFileName);
    char localBuffer[128];
    // Helper Print Statement
    printf("Loading room [%s]\n", localFileName);
    // Open file to read and load
    FILE * roomFile = fopen(localFileName, "r");
    if (roomFile == NULL)
    {
        printf("Error Loading room [%s] [%s]\n", roomFileName, strerror(errno));
        exit(-2);
    }
    // Get the first line
    fgets(localBuffer, 128, roomFile);
    // Main loop to parse file. 3 different cases
    do
    {
        localBuffer[strlen(localBuffer) - 1] = 0x00;
        if (strstr(localBuffer, "ROOM NAME"))
        {
            //  room name in the destination
            char * token = strtok (localBuffer, ":");
            token = strtok (NULL, ":");
            token++;
            rooms[roomIndex].roomName = strdup(token);
            printf("Room [%d] Name [%s]\n", roomIndex, rooms[roomIndex].roomName);
        }

        if (strstr(localBuffer, "CONNECTION"))
        {
            // store connection in the destination
            char * token = strtok (localBuffer, " ");
            token = strtok (NULL, " ");
            token[1] = 0x00;
            int connectIndex = atoi(token);
            token+=3;
            rooms[roomIndex].roomConnectionIDs[connectIndex] = strdup(token);
            printf("Room [%d] Connection [%d][%s]\n", roomIndex, connectIndex, rooms[roomIndex].roomConnectionIDs[connectIndex]);
        }


        if (strstr(localBuffer, "ROOM TYPE"))
        {
            // store roomType it in the destination
            char * token = strtok(localBuffer, ":");
            token = strtok(NULL, ":");
            token++;
            // Convert from string to enum. Store start and end rooms in global
            if (strstr(token, "START_ROOM"))
            {
                rooms[roomIndex].roomType = ROOM_START;
                startRoom = &rooms[roomIndex];
                currRoom = startRoom;
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
            printf("Room [%d] Type [%d]\n", roomIndex, rooms[roomIndex].roomType);
        }
        fgets(localBuffer, 128, roomFile);
    } while (!feof(roomFile));
    fclose(roomFile);
}

// Function to load all room files.
void loadFiles()
{
    // Open the game directory
    DIR * directoryScanner = opendir(gameDirectory);
    struct dirent * currDirectory;
    int roomIndex = 0;
    // Iterate through all files in the game directory
    while ((currDirectory = readdir(directoryScanner)))
    {
        // If the file contains ".room" then load
        if (strstr(currDirectory->d_name, ".room") != NULL)
        {
            loadRoom(roomIndex++, currDirectory->d_name);
        }
    }
    closedir(directoryScanner);
}

// Find a pointer to a room based the string name
room_t * findRoom(const char * name)
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

// Linking Rooms by pointers instead of the given strings
void linkRooms()
{
    // Loop through all rooms
    int roomIndex = 0;
    for (roomIndex = 0; roomIndex < NUM_ROOMS; roomIndex++)
    {
        room_t * currRoom = &rooms[roomIndex];
        int connectIndex = 0;
        // Loop through all connections in the current room
        for (connectIndex = 0; connectIndex < NUM_CONNECTIONS; connectIndex++)
        {
            // Check if there a string is in the current connection
            if (rooms[roomIndex].roomConnectionIDs[connectIndex])
            {
                // If yes, then assign a pointer to the room in the array.
                rooms[roomIndex].roomConnections[connectIndex] = (struct room_t *)findRoom(rooms[roomIndex].roomConnectionIDs[connectIndex]);
                //printf statements below to check that linking worked
                printf("Linking [%s]->[%s]", rooms[roomIndex].roomName, ((room_t *)rooms[roomIndex].roomConnections[connectIndex])->roomName);
                if (rooms[roomIndex].roomType == ROOM_START)
                {
                    printf(" ->[START]");
                }
                if (rooms[roomIndex].roomType == ROOM_END)
                {
                    printf(" <-[END]");
                }
                printf("\n");
            }
        }
    }
}

//Runs the Game!
int startGame()
{
    // Print current location
    printf("CURRENT LOCATION: %s\n", currRoom->roomName);

    char roomConnections[512];
    char userInput[128];
    memset (roomConnections, 512, 0);
    char * roomConnectStringPtr = roomConnections;
    // Loop through all connections
    int connectIndex = 0;
    for (connectIndex = 0; connectIndex < NUM_CONNECTIONS; connectIndex++)
    {
        // Check if the connection is a pointer to another room
        // If yes, then copy room's name to the current string
        if (currRoom->roomConnections[connectIndex])
        {
            const char * connectionName = ((room_t *)currRoom->roomConnections[connectIndex])->roomName;
            int stringLength = strlen(connectionName);
            memcpy (roomConnectStringPtr, connectionName, stringLength);
            roomConnectStringPtr += stringLength;
            *roomConnectStringPtr = ',';
            roomConnectStringPtr++;
            *roomConnectStringPtr = ' ';
            roomConnectStringPtr++;
        }
    }
    // Back up two characters & clean up the string
    roomConnectStringPtr--;
    roomConnectStringPtr--;
    *roomConnectStringPtr = '.';
    roomConnectStringPtr++;
    *roomConnectStringPtr = 0x00;

    // Print connections
    printf("POSSIBLE CONNECTIONS: %s\n", roomConnections);
    printf("WHERE TO? >");

    // User input
    fgets(userInput, 128, stdin);
    userInput[strlen(userInput) - 1] = 0x00;

    int foundRoom = 0;

    // Check if time command is executed
    if (strcmp(userInput, "time") == 0)
    {
        // timer is ticking switch
        timerTicking = 1;

        // Unlock the mutex
        pthread_mutex_unlock(&timeMutex);

        // Waits here until a context switch occurs into the timer thread
        while (timerTicking);

        // Lock timer mutex
        pthread_mutex_lock(&timeMutex);
        return 0;
    }
    else
    {
        // Iterate through all connections of this room
        int connectIndex = 0;
        for (connectIndex = 0; connectIndex < NUM_CONNECTIONS; connectIndex++)
        {
            if (currRoom->roomConnections[connectIndex])
            {
                if (strcmp(userInput, ((room_t *)currRoom->roomConnections[connectIndex])->roomName) == 0)
                {
                    // If we found a connection to a new room, then move to new room
                    currRoom = (room_t *)currRoom->roomConnections[connectIndex];
                    foundRoom = 1;
                }
            }
        }
    }

    // No room found with that name -> error msg
    if (!foundRoom)
    {
        printf("\nHUH? I DON’T UNDERSTAND THAT ROOM. TRY AGAIN.\n");
        return 0;
    }

    printf("\n");
    return 1;
}

// Print the time and saves a file called currentTime.txt
void * timeFunction(void * context)
{
    // While the main thread is running, time thread runs
    while (timeThreadRunning)
    {
        // Unlock mutux & check if timer is still ticking
        pthread_mutex_lock (&timeMutex);
        if (timeThreadRunning && timerTicking)
        {
            // timerTicking allows the main thread to continue when the mutex is unlocked & is a switch that lets us know what the timer is doing
            timerTicking = 0;
            time_t now;
            time(&now);
            const struct tm * timeNow = localtime(&now);
            char timeString[128];
            memset (timeString, 0, 128);
            strftime(timeString, 128, "%Y-%m-%d %H:%M:%S", timeNow);
            printf("\n %s\n\n", timeString);
            FILE * timeFile = fopen("currentTime.txt", "w");
            if (!timeFile)
            {
                printf("Failed to create to currentTime.txt [%s]", strerror(errno));
                exit(-4);
            }
            timeString[strlen(timeString)] = '\n';
            fwrite(timeString, strlen(timeString), 1, timeFile);
            fclose(timeFile);
        }
        // Unlock the mutex and return to main thread.
        pthread_mutex_unlock(&timeMutex);
    }
}

// Main Prog
int main(int argc, char * argv[])
{
    // Create the timer thread & lock the timer mutex when program starts
    pthread_mutex_lock (&timeMutex);
    if (pthread_create(&timeThread, NULL, timeFunction, NULL))
    {
        printf("Failed to create timer thread!\n");
        exit(-3);
    }
    
    // Allocate program memory
    memset (gameDirectory, 0, sizeof (gameDirectory));
    memset (rooms, 0, sizeof(room_t) * NUM_ROOMS);
    
    // Find the game directory
    // Print an error and exit if no rooms are found
    findNewGameDirectory();
    if (strlen(gameDirectory) == 0)
    {
        printf("No valid game directories found! run lioua.buildsrooms first\n");
        return -1;
    }
    
    // Load game rooms and create links
    loadFiles();
    linkRooms();
    printf("\n");
    printf("Welcome to Adventure!");
    printf("\n");
    
    // Setup the history array and turn counter
    int turnCounter = 0;
    char ** history = (char**)malloc(sizeof (char*));
    
    // Main game loop
    while (currRoom != endRoom)
    {
        // Grab to see if a move occured (status of turn)
        int turnStatus = startGame();
        if (turnStatus)
        {
            history = (char**)realloc (history, sizeof (char*) * (turnCounter + 1));
            history[turnCounter] = strdup(currRoom->roomName);
        }
        turnCounter += turnStatus;
    }

    printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
    printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", turnCounter);
    int historyIndex = 0;
    for (historyIndex = 0; historyIndex < turnCounter; historyIndex++)
    {
        printf("%s\n", history[historyIndex]);
        free (history[historyIndex]);
    }

    // Clean up any memory
    free(history);
    int roomIndex = 0;
    for (roomIndex = 0; roomIndex < NUM_ROOMS; roomIndex++)
    {
        free ((void*)rooms[roomIndex].roomName);
        int connectIndex = 0;
        for (connectIndex = 0; connectIndex < NUM_CONNECTIONS; connectIndex++)
        {
            if (((room_t*)&rooms[roomIndex])->roomConnectionIDs[connectIndex])
            {
                free ((void*)((room_t*)&rooms[roomIndex])->roomConnectionIDs[connectIndex]);
            }
        }
    }
    
    // Shutdown the timer thread
    timeThreadRunning = 0;
    pthread_mutex_unlock(&timeMutex);
    pthread_join(timeThread, NULL);
    return 0;
}