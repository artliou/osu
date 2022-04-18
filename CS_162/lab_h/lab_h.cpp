/*********************************************************************
** Author:       Jeremy Prater
** Date:         August 12, 2016
** Description:  lab_h.cpp
*********************************************************************/

#include <string>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include "lib_flip_display.hpp"
#include "lib_arg_parse.hpp"

#include "fileLoader.hpp"
#include "mergeSortRecursive.hpp"
#include "mergeSortIterative.hpp"

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


    if (customArgParser::arguments.debugEnable == true)
    {
      DebugConsole::SetDebugLevel (1);
    }

    DebugConsole::debug_print (0, true, COLOR_GREEN, "CS_162 lab_h\n\n");

    std::string filename;

    if (customArgParser::arguments.hasFilename == true)
    {
      filename = customArgParser::arguments.filename;
    }
    else
    {
      DebugConsole::debug_print (0, true, COLOR_WHITE, "Enter filename to load: ");
      std::cin >> filename;
    }
    

    fileLoader loaderRecursive(filename.c_str());
    fileLoader loaderIterate(filename.c_str());

    mergeSortRecursive myMergeSortRecursive(loaderRecursive.GetBuffer(), loaderRecursive.GetCount());
    mergeSortIterate myMergeSortIterate(loaderIterate.GetBuffer(), loaderIterate.GetCount());

    myMergeSortRecursive.mergeSort();
    myMergeSortIterate.mergeSort();

    // Exit and return success.
    return 0;
}
