#include <cstring>
#include "wndx.hpp"
#include "wsys.hpp"

wndx::wndx()
    : file("x"), x(0)
{}

int wndx::read(char        *buf, 
               const off_t  i, 
               const size_t nbytes)
{
    if (nbytes > sizeof(x) || i + (nbytes-1) >= sizeof(x))
        return -EINVAL;

    memcpy(buf + i, &x, nbytes);
    return nbytes;
}

int wndx::write(const char  *buf,    // Buffer to write from.
                const off_t  i,      // Index.
                const size_t nbytes) // Number of bytes to write.
{
    if (nbytes > sizeof(x) || i + (nbytes-1) >= sizeof(x))
        return -EINVAL;

    memcpy(rcast<char*>(&x) + i, buf, nbytes);
    return nbytes;
}
