#include <cstring>
#include <iostream>
#include "utf8.hpp"
using namespace std;

utf8c::utf8c()
{
    push_back('\0');
}

void utf8c::set(const byte  *s, 
                const size_t n)
{
    resize(n);
    memcpy(data(), s, n);
}

// Set string of bytes containing an UTF-8 character.
utf8c::utf8c(const byte *s)
{
    auto b = s[0]; // first byte in the sequence.
    int  n = 0;    // number of bytes.

    // Check if it is an ASCII character?
    if (!(b & 0x80000000)) {
        // Set the number of bytes to represent this character to 1.
        set(s, 1);
        return;
    }

    // Count the number of bytes used to store this single character.
    while (b & 0x80000000) {
        n++;
        b <<= 1;
    }
    set(s, n);
}

// Set ASCII character, assuming type 'char' is ASCII.
utf8c::utf8c(const char c)
{
    push_back(c);
}
