#include "transformer.hpp"

///////////////////////////////////////////////////////////////////////////////
//
// char Encryption::transform (char ch)
//
// The transform function for Encryption.
// This adds the encryption key to ch and then performs
// modulo 26 to get an encrypted value.
//
// Parameters:
//        char ch - input character from stream
//
// Return:
//        char - the encrypted value
//

char Encryption::transform (char ch)
{
    int outputCharacter = encryptionKey + ch;
    return (char)(outputCharacter % 26);
}

///////////////////////////////////////////////////////////////////////////////
//
// Encryption::Encryption (int keyToUse)  : Transformer()
//
// Constructor for Encryption.
//
// Parameters:
//        int keyToUse - Encryption key to use in this class instance.
//
// Return:
//        none
//

Encryption::Encryption (int keyToUse)  : Transformer()
{
    encryptionKey = keyToUse;
}
