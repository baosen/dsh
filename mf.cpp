#include "mf.hpp"
#include "msys.hpp"

// Construct mouse file.
mf::mf(const std::string name)
    : file(name)
{}

// Read from mouse.
int mf::read(char *buf, const off_t i, const size_t nbytes)
{
    UNUSED(i);

    // Check if divisible.
    if (sizeof(msys::ev) % nbytes != 0)
        return -EINVAL;

    // Copy mouse event into the buffer.
    return msys::getmot(buf, nbytes / sizeof(msys::ev));
}

// Mouse is read-only.
int mf::write(const char *buf, const off_t i, const size_t nbytes)
{
    UNUSED(buf);
    UNUSED(i);
    UNUSED(nbytes);

    return -EPERM; // Operation not permitted.
}
