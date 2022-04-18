////////////////////////////////////////////////////////////////
//
// CS 344 - Assignment 3
//
// Shell Process functions
//
// Jeremy Prater
//

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

#include "smallsh-process.h"
#include "smallsh.h"

////////////////////////////////////////////////////////////////
//
// static local variables
//

static pid_t * pidList;
static int processCount = 0;

////////////////////////////////////////////////////////////////
//
// Shell Process Functions
//

////////////////////////////////////////////////////////////////
//
// Process the exit status/signal of a command
//
static void ProcessExitStatus(pid_t processID, int exitedStatus, char printMessage)
{
    // Check if a process exited by status
    if (WIFEXITED(exitedStatus) != 0)
    {
        int exitStatus = WEXITSTATUS(exitedStatus);
        // Set and print status if needed
        SetStatus (0, processID, exitStatus);
        if (printMessage)
        {
            fprintf (stdout, " <-- Processs [%d] exited by status [%d]\n", processID, exitStatus);
        }
    }
    else if (WIFSIGNALED(exitedStatus) != 0)
    {
        // Check if a process exited by signal
        int exitSignal = WTERMSIG(exitedStatus);
        SetStatus (1, processID, exitSignal);
        // Set and print signal if needed
        if (printMessage)
        {
            fprintf (stdout, " <-- Processs [%d] exited by signal [%d]\n", processID, exitSignal);
        }
    }
    fflush (stdout);
}

////////////////////////////////////////////////////////////////
//
// Remove a process from the background check list
//
static void RemoveProcess(pid_t pid)
{
    // clean up the memory list...
    processCount--;
    if (processCount == 0)
    {
        free (pidList);
        pidList = 0;
    }
    else
    {
        pid_t * newPidList = (pid_t*)malloc(sizeof (pid_t) * processCount);
        int pidIndex = 0;
        int newPidIndex = 0;
        for (pidIndex = 0; pidIndex < processCount + 1; pidIndex++)
        {
            if (pidList[pidIndex] != pid)
            {
                newPidList[newPidIndex++] = pidList[pidIndex];
            }
        }
        free (pidList);
        pidList = newPidList;
    }
}

////////////////////////////////////////////////////////////////
//
// Init the process manager data
//
void InitProcessManager()
{
    pidList = 0;
}

////////////////////////////////////////////////////////////////
//
// Add a process from the background check list
//
void AddProcess (pid_t processID)
{
    pidList = realloc(pidList, sizeof (pid_t) * ++processCount);
    pidList[processCount - 1] = processID;
}

void CheckBackgroundProcesses()
{
    int pidIndex = 0;
    for (pidIndex = 0; pidIndex < processCount; pidIndex++)
    {

        int exitedStatus = 0;
        if (waitpid(pidList[pidIndex], &exitedStatus, WNOHANG) > 0)
        {
            ProcessExitStatus(pidList[pidIndex], exitedStatus, 1);
            RemoveProcess(pidList[pidIndex]);
        }
    }
}

////////////////////////////////////////////////////////////////
//
// Kill a child process...
// This was never used or called because
// signalling took care of it
//
void KillProcess (pid_t processID)
{

}

////////////////////////////////////////////////////////////////
//
// Wait for a process from the background process to exit
//
void WaitProcess (pid_t processID)
{
    int exitedStatus = 0;
    waitpid(processID, &exitedStatus, 0);
    ProcessExitStatus(processID, exitedStatus, 0);
}