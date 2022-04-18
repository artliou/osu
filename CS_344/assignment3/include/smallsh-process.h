////////////////////////////////////////////////////////////////
//
// CS 344 - Assignment 3
//
// Shell Process functions
//
// Jeremy Prater
//

#ifndef SMALLSH_PROCESS_H
#define SMALLSH_PROCESS_H

#include <unistd.h>

void InitProcessManager();
void AddProcess (pid_t processID);
void KillProcess (pid_t processID);
void WaitProcess (pid_t processID);
void CheckBackgroundProcesses();

#endif // SMALLSH_PROCESS_H