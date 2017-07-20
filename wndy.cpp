#include <cstring>
#include "wndy.hpp"

wndy::wndy()
    : file("y"), y(0)
{}

int wndy::read(char        *buf,     // Buffer to read to.
               const off_t  i,       // Index.
               const size_t nbytes)  // Number of bytes to read.
{
    if (nbytes > sizeof(y) || i + (nbytes-1) >= sizeof(y))
        return -EINVAL;

    memcpy(buf + i, &y, nbytes);
    return nbytes;
}

int wndy::write(const char  *buf,    // Buffer to write from.
                const off_t  i,      // Index.
                const size_t nbytes) // Number of bytes to write.
{
    if (nbytes > sizeof(y) || i + (nbytes-1) >= sizeof(y))
        return -EINVAL;

    memcpy(rcast<char*>(&y) + i, buf, nbytes);
    return nbytes;
}
