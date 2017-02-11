#include <cstdarg>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <fcntl.h>
#include "log.hpp"
#include "scr.hpp"
#include "ptr.hpp"

// Open the framebuffer file.
Scr::Scr() {
    fd = ::open("/dev/fb0", O_RDWR);
    if (fd == -1)
        throw err("Cannot open /dev/fb0!");
    // Setup screen.
    const auto v = vinfo();
    w    = v.xres;
    h    = v.yres;
    bpp  = v.bits_per_pixel;
    // Set offsets to pixel in the RGB value.
    roff = v.red.offset;
    goff = v.green.offset;
    boff = v.blue.offset;
    aoff = v.transp.offset;
    // Set the length in bits to the pixel.
    rl   = v.red.length; 
    gl   = v.green.length; 
    bl   = v.blue.length; 
    al   = v.transp.length;
    printf("Screen resolution: %ux%u, %ubpp\n", v.xres, v.yres, v.bits_per_pixel);
    printf("Offset: R%u, G%u, B%u, A%u\n", roff, goff, boff, aoff);
    printf("Color: RGBA%u%u%u%u\n", rl, gl, bl, al);
}

// Close framebuffer file.
Scr::~Scr() {
    if (close(fd) == -1)
        die("Failed to close /dev/fb0!");
}

// Control screen.
#define CTL(req, ...) ioctl(fd, req, __VA_ARGS__)

// Map framebuffer to computer's address space.
Ptr Scr::map() {
    Ptr(*this);
}

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
