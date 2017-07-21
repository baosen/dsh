#include <cstring>
#include "gn.hpp"
#include "wsys.hpp"
#include "wndy.hpp"

wndy::wndy()
    : file("y")
{}

int wndy::read(const char  *path,
               char        *buf,     // Buffer to read to.
               const off_t  i,       // Index.
               const size_t nbytes)  // Number of bytes to read.
{
    uint y;

    if (nbytes > sizeof(y) || i + (nbytes-1) >= sizeof(y))
        return -EINVAL;

    y = wsys::gety(getname(path).data());
    memcpy(buf + i, &y, nbytes);

    return nbytes;
}

int wndy::write(const char  *path,
                const char  *buf,    // Buffer to write from.
                const off_t  i,      // Index.
                const size_t nbytes) // Number of bytes to write.
{
    uint y = 0;

    if (nbytes > sizeof(y) || i + (nbytes-1) >= sizeof(y))
        return -EINVAL;

    memcpy(rcast<char*>(&y) + i, buf, nbytes);
    wsys::movey(getname(path).data(), y);

    return nbytes;
}
