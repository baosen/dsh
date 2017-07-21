#include <cstring>
#include <vector>
#include "wsys.hpp"
#include "wndx.hpp"
#include "gn.hpp"
using namespace std;

// Unsigned int x coordinate file for window.
// TODO: Make /wnd/0/xc for x ascii.

wndx::wndx(const shared_ptr<wndd>& p)
    : parent(p), file("x")
{}

wndx::wndx()
    : file("x")
{}

int wndx::read(const char  *path,   // File path.
               char        *buf,    // Buffer to read from.
               const off_t  i,      // Offset.
               const size_t nbytes) // Number of bytes to read.
{
    uint x;

    // TODO: Change to divisible check?
    if (nbytes > sizeof(x) || i + (nbytes-1) >= sizeof(x))
        return -EINVAL;

    x = wsys::getx(getname(path).data());
    memcpy(buf + i, &x, nbytes);

    return nbytes;
}

int wndx::write(const char  *path,   // File path.
                const char  *buf,    // Buffer to write from.
                const off_t  i,      // Index.
                const size_t nbytes) // Number of bytes to write.
{
    uint x = 0;

    // TODO: Change to divisible check?
    if (nbytes > sizeof(x) || i + (nbytes-1) >= sizeof(x))
        return -EINVAL;

    memcpy(rcast<char*>(&x) + i, buf, nbytes);
    wsys::movex(getname(path).data(), x);

    return nbytes;
}
