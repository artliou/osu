/* CS261- Assignment 0*/
/* Name: Jeremy Prater
 * Date: Sept 25, 2016
 * Solution description: Convert Inches to Centimeters
 */
 
#include <stdio.h>

#include "lib_arg_parse.hpp"
#include "lib_flip_display.hpp"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
//
// Local function definitions
//

float ConvertinTocm (float inches);


///////////////////////////////////////////////////////////////////////////////
//
// int main(int argc, char * argv[])
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
    // Parse command line arguments
    customArgParser::InitalizeArguments();
    error_t error = argp_parse (&customArgParser::argp, argc, argv, 0, 0, &customArgParser::arguments);
    if (error < 0)
    {
        return error;
    }

    DebugConsole::debug_print (0, true, COLOR_GREEN, "CS-261 assignment 0\n\n");

    DebugConsole::debug_print (0, false, COLOR_WHITE, "Using inches: %f\n\n", customArgParser::arguments.userInches);

    DebugConsole::debug_print (0, false, COLOR_WHITE, "%f inches in centimeters is %f cm\n\n",
            customArgParser::arguments.userInches,
            ConvertinTocm(customArgParser::arguments.userInches));
}

///////////////////////////////////////////////////////////////////////////////
//
// float ConvertinTocm (float inches)
//
// Convert Inches to Centimeters
//
// Parameters:
//        float inches - inch distance to convert
//
// Return:
//        float cm - the centimeter equivalent of inches
//

float ConvertinTocm (float inches)
{
    const float InToCm = 2.54;
    return inches * InToCm;
}