#include <cstdarg>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "log.hpp"
#include "scr.hpp"

// Setup screen.
Scr::Scr() {
    // Open the framebuffer file.
    fd = ::open("/dev/fb0", O_RDWR);
    if (fd == -1)
        throw err("Cannot open /dev/fb0!");
#ifdef DEBUG
    // Get variable screen information.
    const auto v = vinfo();
    // Display screen resolution.
    printf("Screen resolution: %ux%u, %ubpp\n", v.xres, v.yres, v.bits_per_pixel);
    // Display the offsets to pixel in the RGB value.
    printf("Pixel offset: R%u, G%u, B%u, A%u\n",   v.red.offset, v.green.offset, v.blue.offset, v.transp.offset);
    // Display the length in bits of a screen pixel.
    printf("Color format: RGBA%u%u%u%u\n", v.red.length, v.green.length, v.blue.length, v.transp.length);
#endif
}

// Close framebuffer file.
Scr::~Scr() {
    if (close(fd) == -1)
        die("Failed to close /dev/fb0!");
}

// Control screen.
#define CTL(req, ...) ioctl(fd, req, __VA_ARGS__)

// Returns framebuffer variable screen info.
Scr::varinfo Scr::vinfo() {
    varinfo v;
    if (CTL(FBIOGET_VSCREENINFO, &v))
        throw err("Can't read video screen information.");
    return v;
}

// Returns framebuffer fixed screen info.
Scr::fixinfo Scr::finfo() {
    fixinfo f;
    if (CTL(FBIOGET_FSCREENINFO, &f))
        throw err("Can't read fixed screen information.");
    return f;
}
