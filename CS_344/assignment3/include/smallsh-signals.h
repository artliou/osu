////////////////////////////////////////////////////////////////
//
// CS 344 - Assignment 3
//
// Shell signal handlers
//
// Jeremy Prater
//

#ifndef SMALLSH_SIGNALS_H
#define SMALLSH_SIGNALS_H

void catchSIGINT(int signo);
void catchSIGSTP(int signo);
void RegisterSignalHandlers();

#endif // SMALLSH_SIGNALS_H