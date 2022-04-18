////////////////////////////////////////////////////////////////
//
// CS 344 - Assignment 3
//
// Shell main functions
//
// Jeremy Prater
//

#ifndef SMALLSH_H
#define SMALLSH_H

void ToggleForegroundOnly();
int GetToggleForegroundOnly();
void SetStatus (int wasSignal, int processID, int exitValue);

#endif // SMALLSH_H