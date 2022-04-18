/*********************************************************************
** Author:       Jeremy Prater
** Date:         July 24, 2016
** Description:  lib_arg_parse.cpp
*********************************************************************/

#include <argp.h>
#include <cstring>
#include "lib_arg_parse.hpp"
#include "lib_flip_display.hpp"
#include <stdio.h>

/*********************************************************************
**
** This file has poor comments because it is for parsing command
** line arguments
**
** No program/assignement logic is contained within this file.
**
*********************************************************************/

const char *argp_program_version = "CS-261 Assignment 0 v1.0";
const char *argp_program_bug_address = "<praterj@oregonstate.edu>";

// Description of the program
const char * customArgParser::doc = "CS-261 Assignment 0 v1.0";

// Description of accepted arguments
const char * customArgParser::args_doc = "";

// Array of command line arguments
// Terminated with a null entry
struct argp_option customArgParser::options[] =
{
    {"inches",  'i', "userInches",      0,  "Inches to convert" },
    { 0 }
};

struct argp customArgParser::argp = { options, parse_opt, args_doc, doc };

struct customArguments customArgParser::arguments;

void customArgParser::InitalizeArguments()
{
  memset (&customArgParser::arguments, 0, sizeof (customArgParser::arguments));
}

error_t customArgParser::parse_opt (int key, char *arg, struct argp_state *state)
{
  /* Get the input argument from argp_parse, which we
     know is a pointer to our arguments structure. */
  struct customArguments *arguments = (struct customArguments *)state->input;

  switch (key)
    {
    case 'i':
      if (sscanf (arg, "%f", &arguments->userInches) != 1)
      {
        DebugConsole::debug_print(0, true, COLOR_RED, "Invalid Number: %s\n\n", arg);
        return -1;
      }
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
