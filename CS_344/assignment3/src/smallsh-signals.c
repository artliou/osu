////////////////////////////////////////////////////////////////
//
// CS 344 - Assignment 3
//
// Shell signal handlers
//
// Jeremy Prater
//

#include "smallsh-signals.h"
#include "smallsh.h"
#include <signal.h>
#include <stdio.h>
#include <string.h>

////////////////////////////////////////////////////////////////
//
// Signal handler for SIGINT
//

void signalSIGINT(int signo)
{
    fprintf (stdout, "\n\nSIGINT : Terminating child foreground processes\n");
    fflush(stdout);
}    

////////////////////////////////////////////////////////////////
//
// Signal handler for SIGSTP
//

void signalSIGSTP(int signo)
{
    ToggleForegroundOnly();
    if (GetToggleForegroundOnly())
    {
        fprintf (stdout, "\n\nSIGTSTP : Background proccess are disabled\n");
        fflush(stdout);
    }
    else
    {
        fprintf (stdout, "\n\nSIGTSTP : Background proccess are enabled\n");
        fflush(stdout);
    }
}

////////////////////////////////////////////////////////////////
//
// Register signal handlers with OS
//

void RegisterSignalHandlers()
{
    struct sigaction handler;
    memset (&handler, 0, sizeof (struct sigaction));

    handler.sa_handler = signalSIGINT;
    sigfillset(&handler.sa_mask);
    handler.sa_flags = 0;
    sigaction (SIGINT, &handler, NULL);

    handler.sa_handler = signalSIGSTP;
    sigfillset(&handler.sa_mask);
    handler.sa_flags = 0;
    sigaction (SIGTSTP, &handler, NULL);
}
