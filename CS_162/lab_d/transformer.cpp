#include "transformer.hpp"

///////////////////////////////////////////////////////////////////////////////
//
// void Transformer::doFilter (std::ifstream &in, std::ofstream & out)
//
// This is the doFilter function for OrderedOutput. It reads all characters
// from in. Calls the transform function on the data, and sends the result
// to the output stream.
// The input stream is reset at the end of this function to allow
// consecutive calls to doFilter for reading the stream
//
// Parameters:
//        std::ifstream &in - input stream
//        std::ofstream &out - output stream
//
// Return:
//        none
//

void Transformer::doFilter (std::ifstream &in, std::ofstream & out)
{
    // Read all ifstream
    char data;
    while (in.get(data))
    {
        // Call transformer
        // ofstream write
        out << transform (data);
    }

    // Reset stream for next filter
    in.clear();
    in.seekg (0, std::ios::beg);
}
