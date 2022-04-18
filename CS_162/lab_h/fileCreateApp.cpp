#include "fileCreator.hpp"
#include "lib_arg_parse-create.hpp"
#include "lib_flip_display.hpp"

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

    if (customArgParser::arguments.validState == 2)
    {
        return fileCreator::createFileDirect(customArgParser::arguments.filename, customArgParser::arguments.numItems);
    }
    if (customArgParser::arguments.validState == 1)
    {
        DebugConsole::debug_print (0, true, COLOR_RED, "Both filename (-f) and number of items (-c) must be specififed!\n\n");
        return -1;
    }
    return fileCreator::createFile();
}