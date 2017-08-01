#include <cstring>
#include <string>
#include "wsys.hpp"
#include "wndyc.hpp"
using namespace std;

// Create window ASCII file y.
wndyc::wndyc(const std::string& p)
    : file("yc"), 
      pname(p)   // Parent directory name.
{}

// Read window x coordinate.
int wndyc::read(char        *buf,    // Buffer to read from.
                const off_t  i,      // Offset.
                const size_t nbytes) // Number of bytes to read.
{
    // TODO: Check if app ask too much?

    const auto s   = to_string(wsys::gety(pname.c_str()));
    const auto len = s.size();

    // Check if app wants less bytes and copy that amount.
    if (nbytes < len) {
        memcpy(buf + i, s.c_str(), nbytes);
        return nbytes;
    }

    // nbytes >= length of string.
    memcpy(buf + i, s.c_str(), len);
    return len;
}

// Write window x coordinate.
int wndyc::write(const char  *buf,    // Buffer to write from.
                 const off_t  i,      // Offset.
                 const size_t nbytes) // Number of bytes to write.
{
    UNUSED(i);
    UNUSED(nbytes);

    wsys::movey(pname.c_str(), 
                atoi(buf));

    // TODO: I am faking the return value here.
    return nbytes;
}
