#include "mf.hpp"
#include "msys.hpp"

// Read from mouse.
int mf::read(char *buf, const off_t i, const size_t nbytes)
{
    // Check if divisible.
    if (sizeof(msys::ev) % nbytes != 0)
        return -EINVAL;

    // Copy mouse event into the buffer.
    return msys::getmot(buf, nbytes / sizeof(msys::ev));
}

// Mouse is read-only.
int mf::write(const char *buf, const off_t i, const size_t nbytes)
{
    return -EPERM; // Operation not permitted.
}
