////////////////////////////////////////////////////////////////
//
// CS 344 - Assignment 3
//
// smallsh
//
// Jeremy Prater
//

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#include "smallsh-shell.h"
#include "smallsh-process.h"
#include "smallsh-signals.h"

////////////////////////////////////////////////////////////////
//
// static local variable data storage
//

static char inputBuffer[MAX_SHELL_INPUT];
static int foregroundOnly = 0;

static int statusWasSignal = 0;
static int statusProcessID = 0;
static int statusExitValue = 0;

////////////////////////////////////////////////////////////////
//
// Called by SIGSTP to toggle the status of foreground only mode
//
void ToggleForegroundOnly()
{
    foregroundOnly = !foregroundOnly;
}

////////////////////////////////////////////////////////////////
//
// Called by the process manager to check if background
// processes are allowed
//

int GetToggleForegroundOnly()
{
    return foregroundOnly;
}

////////////////////////////////////////////////////////////////
//
// Called by the process manager to set the status of an
// exiting program by signal or status
//

void SetStatus (int wasSignal, int processID, int exitValue)
{
    statusWasSignal = wasSignal;
    statusProcessID = processID;
    statusExitValue = exitValue;
}

////////////////////////////////////////////////////////////////
//
// Program entry point
//

int main(int argc, char * argv[])
{
    // Preform initialization functions
    RegisterSignalHandlers();
    InitProcessManager();
    int running = 1;

    // Loop while the shell is running
    while (running)
    {
        // Clear input
        memset (inputBuffer, 0, sizeof (inputBuffer));
        // Check all backgrounded processes for termination.
        CheckBackgroundProcesses();
        // Get Input
        GetInput(inputBuffer);
        struct parsedCommandLine currentCommand = ProcessCommand(inputBuffer);

        // Process the command line
        switch (currentCommand.commandType)
        {
            case SHELL_CMD_EXIT:
            {
                // Time for the shell to exit
                running = 0;
            }
            break;
            case SHELL_CMD_CD:
            {
                // Change directory
                if (currentCommand.argc > 2)
                {
                    fprintf (stdout, "Changing directory to [%s]\n", currentCommand.argv[1]);
                    if (chdir(currentCommand.argv[1]))
                    {
                        // Print error status
                        fprintf (stdout, "Failed to change directory to [%s] [%s]\n", currentCommand.argv[1], strerror(errno));
                    }
                }
                else
                {
                    // Print no path specified
                    fprintf (stdout, "cd: no directory specified\n");
                }
                fflush(stdout);
            }
            break;
            case SHELL_CMD_STATUS:
            {
                // Print the status message for signal or status
                if (statusWasSignal)
                {
                    fprintf (stdout, "Process [%d] exited with signal [%d]\n", statusProcessID, statusExitValue);
                }
                else
                {
                    fprintf (stdout, "Process [%d] exited with status [%d]\n", statusProcessID, statusExitValue);
                }
                fflush (stdout);

            }
            break;
            case SHELL_CMD_EXTERNAL:
            {
                // Execute external command
                // Check background status
                currentCommand.background &= !GetToggleForegroundOnly();
                pid_t spawnPID = fork();
                switch (spawnPID)
                {
                    case -1:
                    {
                        // Something bad happend... To many processes?
                        fprintf (stdout, "system failure... [%s]\n", strerror(errno));
                        fflush (stdout);
                        exit (-1);
                    }
                    break;
                    case 0:
                    {
                        // This is the child. Execute the commands!
                        // Check if we have an input file
                        if (currentCommand.inputFile)
                        {
                            // Open file
                            int inputFileFD = open (currentCommand.inputFile, O_RDONLY);
                            if (inputFileFD < 0)
                            {
                                // Print error if file does not exist
                                fprintf (stdout, "Failed to open [%s] [%s]\n", currentCommand.inputFile, strerror(errno));
                                fflush (stdout);
                                exit(errno);
                            }
                            // Dup2 the fd
                            if (dup2(inputFileFD, 0) == -1)
                            {
                                // Print error if dup2 failed
                                fprintf (stdout, "inputFD dup2 failed [%s]\n", strerror(errno));
                                fflush (stdout);
                                exit(errno);
                            }
                        }
                        else if (currentCommand.background)
                        {
                            // Redirect background input to /dev/null
                            int inputFileFD = open ("/dev/null", O_RDONLY);
                            if (inputFileFD < 0)
                            {
                                // We should always be able to open /dev/null
                                fprintf (stdout, "Failed to open [/dev/null] [%s]\n", strerror(errno));
                                fflush (stdout);
                                exit(errno);
                            }
                            if (dup2(inputFileFD, 0) == -1)
                            {
                                // Print error if dup2 failed
                                fprintf (stdout, "inputFD dup2 failed [%s]\n", strerror(errno));
                                fflush (stdout);
                                exit(errno);
                            }
                        }

                        // Check if we have an output file
                        if (currentCommand.outputFile)
                        {
                            // Open file
                            int outputFileFD = open (currentCommand.outputFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                            if (outputFileFD < 0)
                            {
                                // Print error if file does not exist
                                fprintf (stdout, "Failed to open [%s] [%s]\n", currentCommand.outputFile, strerror(errno));
                                fflush (stdout);
                                exit(errno);
                            }

                            if (dup2(outputFileFD, 1) == -1)
                            {
                                // Print error if dup2 failed
                                fprintf (stdout, "outputFD dup2 failed [%s]\n", strerror(errno));
                                fflush (stdout);
                                exit(errno);
                            }
                        }
                        else if (currentCommand.background)
                        {
                            // Redirect background input to /dev/null
                            int outputFileFD = open ("/dev/null", O_WRONLY);
                            if (outputFileFD < 0)
                            {
                                // We should always be able to open /dev/null
                                fprintf (stdout, "Failed to open [/dev/null] [%s]\n", strerror(errno));
                                fflush (stdout);
                                exit(errno);
                            }

                            if (dup2(outputFileFD, 1) == -1)
                            {
                                // Print error if dup2 failed
                                fprintf (stdout, "inputFD dup2 failed [%s]\n", strerror(errno));
                                fflush (stdout);
                                exit(errno);
                            }
                        }

                        if (execvp (currentCommand.argv[0], &currentCommand.argv[0]) == -1)
                        {
                            // The command failed for some reason.... Print the error and exit with status
                            fprintf (stdout, "Command failed! [%s]\n", strerror(errno));
                            fflush(stdout);
                            exit (errno);
                        }
                    }
                    break;
                    default:
                    {
                        // I'm the parent... Monitor the child process
                        if (!currentCommand.background)
                        {
                            // This is foreground process
                            WaitProcess(spawnPID);
                        }
                        else
                        {
                            // This is background process
                            AddProcess(spawnPID);
                            fprintf (stdout, " --> [%s] is running as background pid [%d]\n", currentCommand.argv[0], spawnPID);
                            fflush (stdout);
                        }
                    }
                    break;
                }
            }
            break;
        }
        // Free the memory used by the currentCommand structure
        CleanupCommandLine(&currentCommand);
    }
}