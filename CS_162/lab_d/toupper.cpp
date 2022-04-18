#include "transformer.hpp"
#include "toupper.hpp"

///////////////////////////////////////////////////////////////////////////////
//
// char ToUpper::transform (char ch)
//
// The transform function for ToUpper.
// If ch is a lower-case letter, it is converted to upper case by
// subtracting the ASCII offset between 'A' and 'a'
//
// Parameters:
//        char ch - input character from stream
//
// Return:
//        char - the upper-case letter
//

char ToUpper::transform (char ch)
{
    // If ch is a lower case, change it to a upper case.
    if ((ch >= LOWER_A) && (ch <= LOWER_Z))
    {
        ch -= LOWER_TO_UPPER_OFFSET;
    }
    return ch;
}
