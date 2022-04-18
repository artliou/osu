/*********************************************************************
** Author:       Jeremy Prater
** Date:         August 1, 2016
** Description:  final.cpp
*********************************************************************/

#include <string>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include "lib_flip_display.hpp"
#include "lib_arg_parse.hpp"

#include "gameSpace.hpp"
#include "gameSpaceController.hpp"
#include "gamePlayer.hpp"
#include "gameObject.hpp"
#include "gameState.hpp"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
//
// Local function definitions
//

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
    // Parse command line rguments
    customArgParser::InitalizeArguments();
    argp_parse (&customArgParser::argp, argc, argv, 0, 0, &customArgParser::arguments);

    DebugConsole::debug_print (0, true, COLOR_GREEN, "CS_162 adventure game (final)\n\n");

    if (customArgParser::arguments.debugEnable == true)
    {
      DebugConsole::SetDebugLevel (1);
    }

    // Create the game state object
    gameState * state = new gameState();

    // Start the game
    state->GameLoop();

    // Clean up any left over objects
    delete state;

    // Exit and return success.
    return 0;
}
