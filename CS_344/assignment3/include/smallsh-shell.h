////////////////////////////////////////////////////////////////
//
// CS 344 - Assignment 3
//
// Shell functions
//
// Jeremy Prater
//

#ifndef SMALLSH_SHELL_H
#define SMALLSH_SHELL_H

////////////////////////////////////////////////////////////////
//
// Define MAX input suzes
//

#define MAX_SHELL_INPUT 2048
#define MAX_SHELL_ARGS 512

////////////////////////////////////////////////////////////////
//
// Shell command enum
//

typedef enum
{
    SHELL_CMD_EXIT     = 0x00,
    SHELL_CMD_CD       = 0x01,
    SHELL_CMD_STATUS   = 0x02,
    SHELL_CMD_EXTERNAL = 0x03,
    SHELL_CMD_COMMENT  = 0x04,
} SHELL_CMD;

////////////////////////////////////////////////////////////////
//
// Structure to hold shell command input
//

struct parsedCommandLine
{
    SHELL_CMD commandType;
    int argc;
    char ** argv;
    char * outputFile;
    char * inputFile;
    unsigned char background;
};


////////////////////////////////////////////////////////////////
//
// Shell processing functions
//

char * GetInput(char * input);
struct parsedCommandLine ProcessCommand(char * input);
void CleanupCommandLine (struct parsedCommandLine * commandLine);

#endif // SMALLSH_SHELL_H