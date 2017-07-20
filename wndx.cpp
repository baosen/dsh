#include <cstring>
#include <vector>
#include "wsys.hpp"
#include "wndx.hpp"
using namespace std;

// Unsigned int x coordinate file for window.
// TODO: Make /wnd/0/xc for x ascii.
wndx::wndx()
    : file("x")
{}

static vector<char> getname(const char *s)
{
    const char *p[2] = {0};

    while (*s) {
        if (*s == '/') {
            swap(p[1], p[0]);
            p[1] = s;
        }
        ++s;
    }
    p[0]++;
    p[1]++;

    vector<char> v(p[1] - p[0] + 1);

    int i = 0;
    while (p[1] != p[0]) {
        v[i] = *p[0];
        p[0]++;
        i++;
    }
    v[v.size()-1] = '\0';

    return v;
}

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
