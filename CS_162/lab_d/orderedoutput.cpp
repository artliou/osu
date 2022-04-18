#include "transformer.hpp"
#include "toupper.hpp"

///////////////////////////////////////////////////////////////////////////////
//
// void OrderedOutput::doFilter (std::ifstream &in, std::ofstream & out)
//
// This is the doFilter function for OrderedOutput. It reads all characters
// from in.Lower case characters are converted to upper case. All new lines
// and white space is removed (ignored). Every 5th character, a space is
// inserted. Numbers and special characters are not modified.
//
// Parameters:
//        std::ifstream &in - input stream
//        std::ofstream &out - output stream
//
// Return:
//        none
//

void OrderedOutput::doFilter (std::ifstream &in, std::ofstream &out)
{
    int characterCounter = 0;
    char data;
    while (in.get(data))
    {
        if ((data != '\n') && (data != '\r') && (data != ' '))
        {
            out << transform (data);
            characterCounter++;
            if (characterCounter == 5)
            {
                characterCounter = 0;
                out << " ";
            }
        }
    }
    in.clear();
    in.seekg (0, std::ios::beg);
}

///////////////////////////////////////////////////////////////////////////////
//
// char OrderedOutput::transform (char ch)
//
// The transform function for OrderedOutput.
// If ch is a lower-case letter, it is converted to upper case by
// subtracting the ASCII offset between 'A' and 'a'
//
// Parameters:
//        char ch - input character from stream
//
// Return:
//        char - the upper-case letter
//

char OrderedOutput::transform (char ch)
{
    // If ch is a lower case, change it to a upper case.
    if ((ch >= LOWER_A) && (ch <= LOWER_Z))
    {
        ch -= LOWER_TO_UPPER_OFFSET;
    }
    return ch;
}
