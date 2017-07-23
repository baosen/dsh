#include <cstring>
#include "gn.hpp"
#include "wsys.hpp"
#include "wndy.hpp"

wndy::wndy(const std::string& p)
    : file("y"), pname(p)
{}

int wndy::read(char        *buf,     // Buffer to read to.
               const off_t  i,       // Index.
               const size_t nbytes)  // Number of bytes to read.
{
    uint y;

    if (nbytes > sizeof(y) || i + (nbytes-1) >= sizeof(y))
        return -EINVAL;

    y = wsys::gety(pname.c_str());
    memcpy(buf + i, &y, nbytes);

    return nbytes;
}

int wndy::write(const char  *buf,    // Buffer to write from.
                const off_t  i,      // Index.
                const size_t nbytes) // Number of bytes to write.
{
    uint y = 0;

    if (nbytes > sizeof(y) || i + (nbytes-1) >= sizeof(y))
        return -EINVAL;

    memcpy(rcast<char*>(&y) + i, buf, nbytes);
    wsys::movey(pname.c_str(), y);

    return nbytes;
}
