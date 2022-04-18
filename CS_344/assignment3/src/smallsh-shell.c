////////////////////////////////////////////////////////////////
//
// CS 344 - Assignment 3
//
// Shell functions
//
// Jeremy Prater
//

#include "smallsh-shell.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

////////////////////////////////////////////////////////////////
//
// Parse a command line input and output a structure into
// struct parsedCommandLine * commandLine
//
// This is the command line tokenizer
//
static void parseCommandLine(char * input, struct parsedCommandLine * commandLine)
{
    // Strip trailing eol off command line
    int strLen = strlen (input);
    input[strLen - 1] = 0x00;

    // Get initial command
    input = strtok(input, " ");

    // Initalize commandLine struct data
    commandLine->argc = 0;
    commandLine->argv = 0;
    commandLine->outputFile = 0;
    commandLine->inputFile = 0;
    commandLine->background = 0;

    // Setup flags for < and >
    unsigned char nextArgumentIsInputFile = 0;
    unsigned char nextArgumentIsOutputFile = 0;

    // NULL check the input and assign argv[0] as the first token (command name)
    if (input != 0)
    {
        commandLine->argc++;
        commandLine->argv = (char **)realloc(commandLine->argv, sizeof (char *) * commandLine->argc);
        commandLine->argv[commandLine->argc - 1] = strdup(input);
    }

    // Append command arguments
    input = strtok(0, " ");
    char * lastToken = 0;

    // Iterate through all tokens seperated by " " and
    // append to the commandline struct
    // The last token is a NULL and we should terminate.
    while (input != 0)
    {
        lastToken = input;
        if (strcmp(input, "<") == 0)
        {
            // The next argument is an input file
            nextArgumentIsInputFile = 1;
        }
        else if (nextArgumentIsInputFile == 1)
        {
            // Set this argument as the input file (stdin)
            nextArgumentIsInputFile = 0;
            commandLine->inputFile = strdup(input);
        }
        else if (strcmp(input, ">") == 0)
        {
            // The next argument is an output file
            nextArgumentIsOutputFile = 1;
        }
        else if (nextArgumentIsOutputFile == 1)
        {
            // Set this argument as the output file (stdout)
            nextArgumentIsOutputFile = 0;
            commandLine->outputFile = strdup(input);
        }
        else
        {
            // The command is a regular argument for the command in argv[0]
            commandLine->argv = (char **)realloc(commandLine->argv, sizeof (char *) * ++commandLine->argc);
            char * argument = strdup (input);
            char * pidExpand = strstr (argument, "$$");
            if (pidExpand)
            {
                // We must expand $$ into the pid of the running process.
                char pidString[10];
                memset (pidString, 0, 10);
                pid_t pid = getpid();
                snprintf(pidString, 10, "%d", pid);
                int pidLength = strlen(pidString);
                int argumentLength = strlen (argument);

                int newArgSize = argumentLength + pidLength - 1;
                argument = (char*) realloc(argument, newArgSize);
                pidExpand = strstr (argument, "$$");
                if (argument + argumentLength > pidExpand + 2)
                {
                    // Extra text!
                    memmove (pidExpand + pidLength, pidExpand + 2 , strlen(pidExpand + 2));  
                }
                memcpy(pidExpand, pidString, pidLength);
                argument[newArgSize - 1] = 0x00;
            }
            commandLine->argv[commandLine->argc - 1] = strdup(argument);
            free(argument);
        }

        // Get the next argument
        input = strtok(0, " ");
    }

    if ((lastToken) && (strcmp(lastToken, "&") == 0))
    {
        commandLine->background = 1;
        commandLine->argc--;
        free (commandLine->argv[commandLine->argc]);
        commandLine->argv = (char **)realloc(commandLine->argv, sizeof (char *) * commandLine->argc);
    }

    // Append trailing null on argv
    commandLine->argc++;
    commandLine->argv = (char **)realloc(commandLine->argv, sizeof (char *) * commandLine->argc);
    commandLine->argv[commandLine->argc - 1] = 0x00;
}

////////////////////////////////////////////////////////////////
//
// Cleanup any memory used by a command line struct
//
void CleanupCommandLine (struct parsedCommandLine * commandLine)
{
    int index = 0;
    for (index = 0; index < commandLine->argc; index++)
    {
        free (commandLine->argv[index]);
    }
    free (commandLine->argv);
}

////////////////////////////////////////////////////////////////
//
// Process an incoming string of text into a command line struct
//
struct parsedCommandLine ProcessCommand(char * input)
{
    struct parsedCommandLine commandLine;
    parseCommandLine(input, &commandLine);

    //printf ("Processing command [%s] with arguments [%d]\n", commandLine.argv[0], commandLine.argc);

    if ((input[0] == '#') || (input[0] == '\n') || (!commandLine.argv[0]))
    {
        commandLine.commandType = SHELL_CMD_COMMENT;
    }
    else if (commandLine.argc > 0)
    {
        if (strcmp (commandLine.argv[0], "exit") == 0)
        {
            commandLine.commandType = SHELL_CMD_EXIT;
        }
        else if (strcmp (commandLine.argv[0], "cd") == 0)
        {
            commandLine.commandType = SHELL_CMD_CD;
        }
        else if (strcmp (commandLine.argv[0], "status") == 0)
        {
            commandLine.commandType = SHELL_CMD_STATUS;
        }
        else
        {
            commandLine.commandType = SHELL_CMD_EXTERNAL;
        }
    }

    return commandLine;
}

////////////////////////////////////////////////////////////////
//
// Get input from stdin (or redirect)
//
char * GetInput(char * input)
{
    fprintf (stdout, ": ");
    fflush(stdout);
    return fgets(input, MAX_SHELL_INPUT, stdin);
}
