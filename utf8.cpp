#include <cstring>
#include <iostream>
#include "utf8.hpp"
using namespace std;

UTF8char::UTF8char()
{
    push_back('\0');
}

void UTF8char::set(const byte  *s, 
                   const size_t n)
{
    resize(n);
    memcpy(data(), s, n);
}

// Set string of bytes containing an UTF-8 character.
UTF8char::UTF8char(const byte *s)
{
    auto b = s[0]; // first byte in the sequence.
    int  n = 0;    // number of bytes.

    // Check if it is an ASCII character?
    if (!(b & 0x80000000)) {
        // Set n = 1.
        set(s, 1);
        return;
    }

    while (b & 0x80000000) {
        n++;
        b <<= 1;
    }
    set(s, n);
}

// Set ASCII character, assuming type 'char' is ASCII.
UTF8char::UTF8char(const char c)
{
    push_back(c);
}
