#ifndef ARG_PARSE_HPP
#define ARG_PARSE_HPP

#include <argp.h>

/*********************************************************************
**
** This file has poor comments because it is for parsing command
** line arguments
**
** No program/assignement logic is contained within this file.
**
*********************************************************************/

// Structure definition for application arguments
struct customArguments
{
  float userInches;
};

class customArgParser
{
private:
  // Description of the program
  static const char * doc;

  // Description of accepted arguments
  static const char * args_doc;

  // Array of command line arguments
  // Terminated with a null entry
  static struct argp_option options[];

  // Parser Function
  static error_t parse_opt (int key, char *arg, struct argp_state *state);

public:

  // External interface to class
  static struct argp argp;
  static struct customArguments arguments;
  static void InitalizeArguments();
};

#endif // ARG_PARSE_HPP
