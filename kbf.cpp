#include <linux/input.h>
#include "types.hpp"
#include "kbsys.hpp"
#include "kbf.hpp"

int kbf::read(char *buf, const off_t i, const size_t nbytes)
{
    // Check if the read is not whole (divisible).
    const auto isize = sizeof(input_event);
    if (isize % nbytes != 0)
        return -EINVAL; // Invalid parameter.

    // Read keyboard input event from keyboard.
    const auto n = isize / nbytes;
    int read = 0;
    for (uint i = 0; i < n; ++i) {
        *rcast<input_event*>(buf) = kbsys::get();
        buf  += isize;
        read += isize;
    }

    // Return number of bytes read.
    return read;
}

int kbf::write(const char *buf, const off_t i, const size_t nbytes)
{
    UNUSED(buf);
    UNUSED(i);
    UNUSED(nbytes);

    return -EPERM; // Operation not permitted.
}
