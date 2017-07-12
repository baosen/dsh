#include <cstring>
#include "utf8.hpp"

UTF8char::UTF8char()
{
    push_back('\0');
}

// Set string of bytes containing an UTF-8 character.
UTF8char::UTF8char(const byte *s)
{
    // TODO!
}

// Set ASCII character, assuming type 'char' is ASCII.
UTF8char::UTF8char(const char c)
{
    push_back(c);
}
