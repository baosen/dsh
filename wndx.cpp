#include <cstring>
#include <vector>
#include "wsys.hpp"
#include "wndx.hpp"
#include "gn.hpp"
using namespace std;

// Unsigned int x coordinate file for window.

// Create window file x.
wndx::wndx(const std::string& p)
    : file("x"), 
      pname(p)   // Parent directory name.
{}

// Read window x coordinate.
int wndx::read(char        *buf,    // Buffer to read from.
               const off_t  i,      // Offset.
               const size_t nbytes) // Number of bytes to read.
{
    uint x;

    // TODO: Change to divisible check?
    if (nbytes > sizeof(x) || i + (nbytes - 1) >= sizeof(x))
        return -EINVAL; // Invalid parameter.

    x = wsys::getx(pname.c_str());
    memcpy(buf + i, &x, nbytes);

    return nbytes;
}

// Write window x coordinate.
int wndx::write(const char  *buf,    // Buffer to write from.
                const off_t  i,      // Offset.
                const size_t nbytes) // Number of bytes to write.
{
    uint x = 0;

    // TODO: Change to divisible check?
    if (nbytes > sizeof(x) || i + (nbytes - 1) >= sizeof(x))
        return -EINVAL; // Invalid parameter.

    memcpy(rcast<byte*>(&x) + i, buf, nbytes);
    wsys::movex(pname.c_str(), x);

    return nbytes;
}
