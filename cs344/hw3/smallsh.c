/***
Arthur Liou
OSU CS 344
Program 3
***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

// File Input and Output
char *inFile;
char *outFile;

// Global Variables
int backgroundProcess = 1;

// Signal Actions Structs
struct sigaction SIGINT_action = {0};
struct sigaction SIGTSTP_action = {0};

// Function Declarations
int changeDirectoryFunction(char**);
int exitFunction();
// int statusFunction(char**, int);
void insertPID(char**, int);
void sigINT(int);
void sigTSTP(int);
void cleanUp(char**, int);
void printStatus(int);

//Function Definitions

//Function to change directories. 
int changeDirectoryFunction(char **userArguments) {
  //If a user just enters 'cd', go to HOME. If statement will get home value. If it exists, changes to home.
  if(userArguments[1] == NULL) {
    char *home = getenv("HOME");
    if(home != NULL) {
      chdir(home);
    }
  }

  // Else, change to the user specified directory
  else {
    char cwd[256];
    char newDirectory[256];
    getcwd(cwd, sizeof(cwd));

    if(strcmp(userArguments[1], "..") != 0) {
      sprintf(newDirectory, "%s/%s", cwd, userArguments[1]);
    }
    else {
      strcpy(newDirectory, "..");
    }
    if(chdir(newDirectory) != 0) {
      printf("No such file or directory ot cd to. \n");
    }
  }
  return 0;
}

int exitFunction() {
  exit(0);
}

// Function to capture and "$$", If "$$",then change to PID
void insertPID(char **userArguments, pid_t spawnPID) {
  char *pch;
  int i = 0;
  int j = 0;
  int argumentLength = 0;
  while(userArguments[i] != NULL) {
    pch = strstr(userArguments[i], "$$");
    if(pch != NULL) {
      argumentLength = strlen(userArguments[i]);
      char *buffer = malloc(sizeof(char) + (argumentLength + 5));
      char *temp1 = malloc(sizeof(char) + (argumentLength + 5));
      char *temp2 = malloc(sizeof(char) + (argumentLength + 5));

      while(userArguments[i] + sizeof(char) * j != pch) {
        temp1[j] = userArguments[i][j];
        j++;
      }

      temp1[j] = '\0';
      j += 2;
      int loc = j;

      while(userArguments[i][j] != '\0') {
        temp2[j - loc] = userArguments[i][j];
        j++;
      }

      temp2[j - loc] = '\0';

      sprintf(buffer, "%s%d%s", temp1, (int) spawnPID, temp2);
      free(temp1);
      free(temp2);
      free(userArguments[i]);
      userArguments[i] = buffer;
    }
    i++;
  }
}

// Function that checks for Ctrl-C
void sigINT(int signo) {
  printf("\nSignal Caught, sleeping for 5 seconds! %d\n", signo);
  //sleep(5);
  SIGINT_action.sa_handler = SIG_IGN;
  sigaction(SIGINT, &SIGINT_action, NULL);
}

// This function checks for Ctrl-Z
void sigTSTP(int signo) {
  char *zMessage = "\nSIGTSTP Detected! ";
  int zLen = strlen(zMessage);
  write(STDOUT_FILENO, zMessage, zLen);

  if(signo == SIGTSTP) {
    if(backgroundProcess == 1) {
      char *message = "Entering foreground only mode (& is ignored)...\n";
      int len = strlen(message);
      write(STDOUT_FILENO, message, len);
      // Flips backgroundProcess switch so processes are not created
      backgroundProcess = 0; 
    }
    else if(backgroundProcess == 0) {
      char *message = "Exiting foreground only mode...\n";
      int len = strlen(message);
      write(STDOUT_FILENO, message, len);
      // Flips backgroundProcess switch so processes can be created
      backgroundProcess = 1; 
    }
  }
}

//Function to clear userarguments array and files,
void cleanUp(char **userArguments, int numArguments) {
  //Clean userArguments array
  int i;
  for(i = 0; i < numArguments; i++) {
    userArguments[i] = NULL;
  }

  // Files will be set to NULL for use again
  inFile = NULL;
  outFile = NULL;
  free(inFile);
  free(outFile);
}

// Print if process has successfully finished. If not, print interrupted signal
void printStatus(int status) {
  if(WIFEXITED(status)) {
    printf("Exit Status: %i\n", WEXITSTATUS(status));
  }
  else {
    printf("Background process interrupted, terminated by signal %i\n", status);
  }
}

//Main Argument
int main() {
  char userLine[2048];
  char *userArguments[512];

  int status = 0;

  // Section to Catch Signals. Action Handlers are setting 
  SIGINT_action.sa_handler = SIG_IGN;
  sigaction(SIGINT, &SIGINT_action, NULL);

  SIGTSTP_action.sa_handler = SIG_IGN;
  SIGTSTP_action.sa_handler = sigTSTP;
  SIGTSTP_action.sa_flags = SA_RESTART;
  sigaction(SIGTSTP, &SIGTSTP_action, NULL);

  // An infinite while loop to keep shell open
  while(1) {
    int numArguments, background = 0;
    printf(": ");
    fflush(stdout);
    // Get the user input. Close if end of file
    if(fgets(userLine, 2048, stdin) == NULL) {
      return;
    }

    //Parses user input
    int pos = 0;
    numArguments = 0;
    char *token;

    // Split user command arguments into tokens by space
    token = strtok(userLine, " \n");
    //Checks tokens for special char, grabs input name, copy token to inFile, and move on to next argument
    while(token != NULL) {
      if(strcmp(token, "<") == 0) {
        token = strtok(NULL, " \n");
        inFile = strdup(token);
        token = strtok(NULL, " \n");
      }
      //Else Grab file nam, copy token to outFile, get the next argument
      else if(strcmp(token, ">") == 0) {
        token = strtok(NULL, " \n");
        outFile = strdup(token);
        token = strtok(NULL, " \n");
      }

      // shows command if in the background
      else if(strcmp(token, "&") == 0) {
        if(backgroundProcess == 1) {
          background = 1;
        }
        // If backgroundProcess is not set to 1, we are in foreground-only mode
        else {
          background = 0;
        }
        break;
      }

      // Store userArguments in an array
      else {
        userArguments[pos] = strdup(token);
        token = strtok(NULL, " \n");
        numArguments++;
        ++pos;
      }
    }

    userArguments[pos] = NULL;
    insertPID(userArguments, getpid());

    //Executes User's Commands
    if(userArguments[0] == NULL) {
    }
    else if(strcmp(userArguments[0], "cd") == 0) {
      changeDirectoryFunction(userArguments);
    }
    else if(strcmp(userArguments[0], "exit") == 0) {
      exitFunction();
    }
    else if(strcmp(userArguments[0], "status") == 0) {
      printStatus(status);
    }

    // Special handler for comments
    else if(!(strncmp(userArguments[0], "#", 1))) {
    }

    // Otherwise, non built in shell functions
    else {
      int FD, i;

      // Call fork
      pid_t spawnPID = fork();

      if(spawnPID == 0) {
        if(!background) {
          // If process isn't in background, can be interrupted with Ctrl-C
          SIGINT_action.sa_handler = SIG_DFL; // Set to default
          SIGINT_action.sa_flags = 0;
          sigfillset(&SIGINT_action.sa_mask);
          sigaction(SIGINT, &SIGINT_action, NULL);
        }
        
        // If input file exists, open check for validity, redirect input, and close
        if(inFile != NULL) {
          FD = open(inFile, O_RDONLY);
          // File is invalid or doesn't exist, exit
          if(FD == -1) {
            fprintf(stderr, "cannot open file for input: %s\n", inFile);
            exit(1);
          }
          else if(dup2(FD, 0) == -1) {
            fprintf(stderr, "DUP2 error. \n");
            exit(1);
          }
          close(FD);
        }

        // if process is in the background, redirect the input to /dev/null if the input file is not specified
        else if(background) {
          FD = open("/dev/null", O_RDONLY);
          if(FD == -1) {
            fprintf(stderr, "Could not open.\n");
            exit(1);
          }
          else if(dup2(FD, 0) == -1) {
            fprintf(stderr, "DUP2 error\n");
            exit(1);
          }
          close(FD);
        }

        // If output file exists, open file, check for errors, then close
        else if(outFile != NULL) {
          FD = open(outFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);

          if(FD == -1) {
            fprintf(stderr, "Could not open file %s\n", outFile);
            fflush(stdout);
            exit(1);
          }

          if(dup2(FD, 1) == -1) {
            fprintf(stderr, "DUP2 error\n");
            exit(1);
          }
          close(FD);
        }

        // Execute the command in userArguments[0]. Unrecognizable command handler
        if(execvp(userArguments[0], userArguments)) {
          fprintf(stderr, "Command not found: %s\n", userArguments[0]);
          fflush(stdout);
          exit(1);
        }
      }
      // Fork Error handling
      else if(spawnPID < 0) {
        fprintf(stderr, "There was an error with fork()\n");
        status = 1;
      }
      //Parent. If process isn't in the background, wait for foreground process to finish
      else {
        if(!background) {
          waitpid(spawnPID, &status, 0);
        }
        // If process is in background, print its PID
        else {
          printf("Background PID: %d\n", spawnPID);
        }
      }

      cleanUp(userArguments, numArguments);

      // Check to see if background processes have completed. 
      spawnPID = waitpid(-1, &status, WNOHANG);
      //Status Printing
      while(spawnPID > 0) {
        printf("Background PID %d is completed. \n", spawnPID);
        printStatus(status);
        spawnPID = waitpid(-1, &status, WNOHANG);
      }

    }
  }

  return 0;
}
