/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 21, 2016
** Description:  lab-e.cpp
*********************************************************************/

#include <string>
#include <iostream>
#include <cstring>
#include "lib_flip_display.hpp"
#include "node.hpp"
#include "nodeController.hpp"
#include <stdlib.h>
#include <argp.h>

using namespace std;

const char *argp_program_version =
  "lab_e 1.0";
const char *argp_program_bug_address =
  "<praterj@oregonstate.edu>";

static char doc[] =
  "lab_e - Linked list";

/* A description of the arguments we accept. */
static char args_doc[] = "";

/* The options we understand. */
static struct argp_option options[] = {
  {"inputData",  'i', "inputData",      0,  "Default data to load into the linked list" },
  { 0 }
};

/* Used by main to communicate with parse_opt. */
struct arguments
{
  char * inputData;
};

/* Parse a single option. */
error_t parse_opt (int key, char *arg, struct argp_state *state)
{
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  struct arguments *arguments = (struct arguments *)state->input;

  switch (key)
    {
    case 'i':
      arguments->inputData = arg;
      break;

    case ARGP_KEY_ARG:
      if (state->arg_num >= 1)
        /* Too many arguments. */
        argp_usage (state);

      //arguments->args[state->arg_num] = arg;

      break;

    case ARGP_KEY_END:
      if (state->arg_num < 0)
        /* Not enough arguments. */
        argp_usage (state);
      break;

    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}

/* Our argp parser. */
static struct argp argp = { options, parse_opt, args_doc, doc };

///////////////////////////////////////////////////////////////////////////////
//
// int main()
//
// Program entry point.
//
// Parameters:
//        int argc - number of command line parameters
//        char * argvp[] - char array of command line parameters
//
// Return:
//        int return code - zero for success
//

int main(int argc, char * argv[])
{
    struct arguments arguments;

    /* Default values. */
    arguments.inputData = __null;

    /* Parse our arguments; every option seen by parse_opt will
       be reflected in arguments. */
    argp_parse (&argp, argc, argv, 0, 0, &arguments);
    NodeController myController;

    if (arguments.inputData != __null)
    {
        int position = 0;
        while (position < strlen (arguments.inputData))
        {
            myController.AddNode(arguments.inputData[position++]);
        }
    }
    else
    {
      debug_print (true, COLOR_CYAN, "\n\nStart typing keys to record Nodes.\nPress ESC to stop and print all nodes.");
      int key = 0;
      while ((key = getkey()) != 0x1B)
      {
        if (key >= 0x20)
        {
          myController.AddNode (key);
        }
      }
    }

    debug_print (true, COLOR_CYAN, "\n\nInput string: ");
    myController.PrintAllItems();
    debug_print (true, COLOR_CYAN, "\n\n");

    return 0;
}
