/***
Arthur Liou
OSU CS 344
Program 3
***/

//Add Dependencies
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

// File Input and Output
// This is to set up the input and output files
char *inFile;
char *outFile;

// Global Variables
// This is to determine if there is a background process running. Also helps when we want to indicate foreground & background process
int backgroundProcess = 1;

// Signal Actions Structs
// Using the sigaction struct to indicate whether 
struct sigaction SIGINT_action = {0};
struct sigaction SIGTSTP_action = {0};

// Function Declarations
// These the the functions that I will be defining and using in my program.
int changeDirectoryFunction(char**);
int exitFunction();
void insertPID(char**, int);
void sigINT(int);
void sigTSTP(int);
void cleanUp(char**, int);
void printStatus(int);

//Function Definitions

//Function to change directories.
// We need a function that will help us change which directory we are in
// We need one userArguments input for what the user types in.
int changeDirectoryFunction(char **userArguments) {
  //If a user just enters 'cd', go to HOME. If statement will get home value. If it exists, changes to home.
  if(userArguments[1] == NULL) {
    char *home = getenv("HOME");
    if(home != NULL) {
      chdir(home);
    }
  }
  // Else, change to the user specified directory
  // if a userArgument is not just cd, they are looking to move to a specific directory they specified
  else {
    // Here I created arrays cwd and newDirectory
    //256 is a typical buffer size, so I have set cwd and newDirectory to this. 
    char cwd[256]; 
    char newDirectory[256];
    getcwd(cwd, sizeof(cwd)); 
    //getcwd gets the current absolute path so we know what directory we are currently in.
    //will place array of characters in array () char cwd[256]). this array of characters is the path of the current working directory

    // Now we have to compare string arguments of [1], where the user has defined a function after "cd"
    if(strcmp(userArguments[1], "..") != 0) {
      sprintf(newDirectory, "%s/%s", cwd, userArguments[1]);
      //this functino will story the user defined directory they weant to go to in newDirectory
    }
    else {
      strcpy(newDirectory, "..");
      //this is to look at if ther user put "cd ..", which is has a unique role/function
    }
    //this checks to see if the user defined directory is valid or not
    if(chdir(newDirectory) != 0) {
      printf("No such file or directory ot cd to. \n");
    }
  }
  return 0;
}

// This is a simple exit function for us to exit out of the program when called upon
int exitFunction() {
  exit(0);
}

// Function to capture and "$$", If "$$",then change to PID
void insertPID(char **userArguments, pid_t spawnPID) {
  //set up local variables for function
  char *pch;
  int i = 0;
  int j = 0;
  int argumentLength = 0;
  // Created a while loop
  while(userArguments[i] != NULL) {
    //test for $$ if first thing in the arguments
    pch = strstr(userArguments[i], "$$");
    //If pch is not NULL, basically if $$ was found, then go into this if-else statement
    if(pch != NULL) {
      //grab the legnth of the argument
      argumentLength = strlen(userArguments[i]);
      // create buffers and temp1 + temp2 to allocate memory
      char *buffer = malloc(sizeof(char) + (argumentLength + 5));
      char *temp1 = malloc(sizeof(char) + (argumentLength + 5));
      char *temp2 = malloc(sizeof(char) + (argumentLength + 5));

      //while loops to iterate through the arguments length until it equals pch
      while(userArguments[i] + sizeof(char) * j != pch) {
        temp1[j] = userArguments[i][j];
        j++;
      }
      //\0 to end this line and skip 2 spots
      temp1[j] = '\0';
      j += 2;
      //get a loc (location) to copy j and start the next while loops
      int loc = j;

      //use this loop to continue on. when userarguments is not equal to end of line
      while(userArguments[i][j] != '\0') {
        temp2[j - loc] = userArguments[i][j];
        j++;
      }
      //\0 to end this line
      temp2[j - loc] = '\0';

      //copy PID over to buffer, free memory for temp1, temp2, and userArguments, and set buffer as userArguments
      sprintf(buffer, "%s%d%s", temp1, (int) spawnPID, temp2);
      free(temp1);
      free(temp2);
      free(userArguments[i]);
      userArguments[i] = buffer;
    }
    //Increament 1
    i++;
  }
}

// Function that checks for Ctrl-C
void sigINT(int signo) {
  printf("\nSignal Caught, sleeping for 5 seconds! %d\n", signo);
  //sleep(5); //Had a sleep function command that was used in testing to sleep for 5 seconds
  // Set up the handler to ignore (SIG_IGN -> ignore)
  SIGINT_action.sa_handler = SIG_IGN;
  //Execute Signal Action. set the disposition for SIGINT to &SIGINT_action and do not store in anything / NULL.
  sigaction(SIGINT, &SIGINT_action, NULL);
}

// This function checks for Ctrl-Z
void sigTSTP(int signo) {
  //Creates a message to show that SIGTSTP or Ctrl-Z is detected ";
  char *zMessage = "\nSIGTSTP Detected! ";
  //Grabs the length of that message
  int zLen = strlen(zMessage);
  //writes it to output
  write(STDOUT_FILENO, zMessage, zLen);

  //checks of the input parameter signo is equal to the SIGTSTP action handler 
  if(signo == SIGTSTP) {
    //if the background backgroundProcess flag is on, then we ignore the process, enter foreground only mode, write to STDOUT, and flip background Process switch/flag to 0/off;
    if(backgroundProcess == 1) {
      char *message = "Entering foreground only mode (& is ignored)...\n";
      int len = strlen(message);
      write(STDOUT_FILENO, message, len);
      // Flips backgroundProcess switch so processes are not created
      backgroundProcess = 0; 
    }
    //if the background backgroundProcess flag is off, exit foreground only mode, write to STDOUT, and flip background Process switch/flag to 1/on;
    else if(backgroundProcess == 0) {
      char *message = "Exiting foreground only mode...\n";
      int len = strlen(message);
      write(STDOUT_FILENO, message, len);
      // Flips backgroundProcess switch so processes can be created
      backgroundProcess = 1; 
    }
  }
}

//Function to clear userArguments array and files.
void cleanUp(char **userArguments, int numArguments) {
  //Clean userArguments array
  //sets a counter i and iterates through all userArguments elements and clears the array out.
  int i;
  for(i = 0; i < numArguments; i++) {
    userArguments[i] = NULL;
  }

  // Files will be set to NULL for use again
  // clean up the inFile and OutFile by changing them to null and freeing up the memory they took
  inFile = NULL;
  outFile = NULL;
  free(inFile);
  free(outFile);
}

// Print if process has successfully finished. If not, print interrupted signal
void printStatus(int status) {
  //IF the Process successfully finished, we print an Exit Status message followed by the status number of that exit status.
  if(WIFEXITED(status)) {
    printf("Exit Status: %i\n", WEXITSTATUS(status));
  }
  //The process did not successfully finish and so I've added a message saring that the Background process interrupted, terminated by signal X
  else {
    printf("Background process interrupted, terminated by signal %i\n", status);
  }
}

//Main Argument
int main() {
  //create arrays to hold userLine inputs and userArguments
  char userLine[2048];
  char *userArguments[512];

  //variable to hold system status
  int status = 0;

  // Section to Catch Signals. Action Handlers are setting 
  SIGINT_action.sa_handler = SIG_IGN;
  sigaction(SIGINT, &SIGINT_action, NULL);

  //Section to ignore TSTP action handler and prep it with sigTSTP. 
  SIGTSTP_action.sa_handler = SIG_IGN;
  SIGTSTP_action.sa_handler = sigTSTP;
  SIGTSTP_action.sa_flags = SA_RESTART;
  sigaction(SIGTSTP, &SIGTSTP_action, NULL);

  // An infinite while loop to keep shell open
  while(1) {
    //local variables for the while loops
    int numArguments, background = 0;
    printf(": "); //Print a : to set up the start of the "ready for input" start
    fflush(stdout); //flush buffers standard output. Proper procedure is to use the printf before hand in the previous line to start clean and set up a new line 

    // Get the user input. Close if end of file
    if(fgets(userLine, 2048, stdin) == NULL) {
      return; //this exits out of the while loop and out of the main
    }

    //Parses user input
    int pos = 0;
    numArguments = 0;
    char *token; //see 2-3 lines below

    // Split user command arguments into tokens by space
    // We split up the user command line inputs into tokens and then create a new line
    token = strtok(userLine, " \n"); //standard function to split a string (userLine here) into into tokens -> hence the name token

    //Checks tokens for special char, grabs input name, copy token to inFile, and move on to next argument
    while(token != NULL) {
      if(strcmp(token, "<") == 0) {
        token = strtok(NULL, " \n"); //split the rest of the token and create a new line
        inFile = strdup(token); //creates a copy of the token and makes the inFile point to this
        token = strtok(NULL, " \n"); //split the rest of the token and create a new line
      }
      //Else Grab file name, copy token to outFile, get the next argument
      else if(strcmp(token, ">") == 0) {
        token = strtok(NULL, " \n"); //split the rest of the token and create a new line
        outFile = strdup(token); //creates a copy of the token and makes the outFile point to this
        token = strtok(NULL, " \n"); //split the rest of the token and create a new line
      }

      // shows command if in the background
      else if(strcmp(token, "&") == 0) {
        //if backgroundProcess is on, then set "background" local variable to 1
        if(backgroundProcess == 1) {
          background = 1;
        }
        // If backgroundProcess is not set to 1, we are in foreground-only mode
        //if backgroundProcess is oof, then set "background" local variable to 0
        else {
          background = 0;
        }
        break; //exit out of while loop
      }

      // Store userArguments in an array
      else {
        //split the tokens up into userArguments array
        userArguments[pos] = strdup(token);
        token = strtok(NULL, " \n");
        numArguments++; //add length of userArguments
        ++pos; //increase pos
      }
    }
    
    //Grab current position and set to null
    userArguments[pos] = NULL;
    //execute insertPID command
    insertPID(userArguments, getpid());

    //Executes User's Commands
    if(userArguments[0] == NULL) {
    }
    //if there's a cd, execute changeDirectoryFunction function
    else if(strcmp(userArguments[0], "cd") == 0) {
      changeDirectoryFunction(userArguments);
    }
    //if there's a cd, execute exit function
    else if(strcmp(userArguments[0], "exit") == 0) {
      exitFunction();
    }
    //if there's a cd, execute status function
    else if(strcmp(userArguments[0], "status") == 0) {
      printStatus(status);
    }

    // Special handler for comments
    else if(!(strncmp(userArguments[0], "#", 1))) {
      //do nothing forever until this userLine ends
    }

    // Otherwise, non built in shell functions
    else {
      //set up filedescriptor var and index variable
      int FD, i;

      // Call fork
      pid_t spawnPID = fork();

      //if we're in PID 0, then check if background exits
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
          FD = open(inFile, O_RDONLY); //open
          // File is invalid or doesn't exist, exit
          if(FD == -1) { //invalid / can't open
            fprintf(stderr, "cannot open file for input: %s\n", inFile); //print to console
            exit(1); //exit program
          }
          else if(dup2(FD, 0) == -1) { //unable to duplicate
            fprintf(stderr, "DUP2 error. \n"); //print to console
            exit(1); //exit program
          }
          close(FD); //deallocates file description
        }

        // if process is in the background, redirect the input to /dev/null if the input file is not specified
        else if(background) {
          FD = open("/dev/null", O_RDONLY); //open
          //if we can't open the file
          if(FD == -1) {
            fprintf(stderr, "Could not open.\n"); //print to console
            exit(1); //exit program
          }
          else if(dup2(FD, 0) == -1) { //unable to duplicate
            fprintf(stderr, "DUP2 error\n"); //print to console
            exit(1); //exit program
          }
          close(FD); //deallocates file description
        }

        // If output file exists, open file, check for errors, then close
        else if(outFile != NULL) {
          FD = open(outFile, O_WRONLY | O_CREAT | O_TRUNC, 0644); //check if output file exists

          if(FD == -1) { //try to open file
            fprintf(stderr, "Could not open file %s\n", outFile);
            fflush(stdout); //write to stdout
            exit(1); //exit program
          }

          if(dup2(FD, 1) == -1) { //unable to duplicate
            fprintf(stderr, "DUP2 error\n"); //write to stdout
            exit(1); //exit program
          }
          close(FD); //deallocates file description
        }

        // Execute the command in userArguments[0]. Unrecognizable command handler
        //if we are unable to find a valid command for what the user inputs
        if(execvp(userArguments[0], userArguments)) {
          fprintf(stderr, "Command not found: %s\n", userArguments[0]);
          fflush(stdout); //write to stdout
          exit(1); //exit function
        }
      }
      // Fork Error handling
      //this is standard, ie if spawnPID isn't 1 (-1 in this case)
      else if(spawnPID < 0) {
        fprintf(stderr, "There was an error with fork()\n"); //print to console
        status = 1; //update status
      }
      //Parent. If process isn't in the background, wait for foreground process to finish
      else {
        if(!background) {
          waitpid(spawnPID, &status, 0); //Waiting for foreground process to finish
        }
        // If process is in background, print its PID
        else {
          printf("Background PID: %d\n", spawnPID);
        }
      }
      //clean up OS and arrays as we are almost done with the main function / program / shell
      cleanUp(userArguments, numArguments);

      // Check to see if background processes have completed. 
      spawnPID = waitpid(-1, &status, WNOHANG);
        //while we are waiting for background process to complete.
      //Status Printing
      while(spawnPID > 0) { 
      //print as PID processes are complete, print to console, and update its spawnPID.
        printf("Background PID %d is completed. \n", spawnPID);
        printStatus(status);
        spawnPID = waitpid(-1, &status, WNOHANG);
      }

    }
  }

  //exit out of main program
  return 0;
}
