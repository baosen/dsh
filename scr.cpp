#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "log.hpp"
#include "scr.hpp"

// Setup framebuffer screen.
Scr::Scr() 
{
    // Open the framebuffer file.
    fd = ::open("/dev/fb0", O_RDWR);
    if (fd < 0)
        throw err("Cannot open /dev/fb0!");
#ifdef DEBUG
    // Get variable screen information.
    const auto v = vinfo();
    // Display screen resolution.
    printf("Screen resolution: %ux%u, %ubpp\n", v.xres, v.yres, v.bits_per_pixel);
    // Display the length in bits of a screen pixel.
    printf("Color format: RGBA%u%u%u%u\n", v.red.length,     // Length of bits representing the color red.
                                           v.green.length,   // Length of bits representing the color green.
                                           v.blue.length,    // Length of bits representing the color blue.
                                           v.transp.length); // Length of bits representing the color alpha.
    // Display the offsets to pixel in the RGB value.
    printf("Pixel offset: R%u, G%u, B%u, A%u\n", v.red.offset, v.green.offset, v.blue.offset, v.transp.offset);
#endif
}

// Close framebuffer file.
Scr::~Scr() 
{
    if (close(fd) < 0)
        die("Failed to close /dev/fb0!");
}

// Control framebuffer screen.
#define CTL(req, ...) ioctl(fd, req, __VA_ARGS__)

// Returns framebuffer variable screen info.
Scr::varinfo Scr::vinfo() 
{
    varinfo v;
    if (CTL(FBIOGET_VSCREENINFO, &v) < 0)
        throw err("Failed to read video screen information from framebuffer file!");
    return v;
}

// Returns framebuffer fixed screen info.
Scr::fixinfo Scr::finfo() 
{
    fixinfo f;
    if (CTL(FBIOGET_FSCREENINFO, &f) < 0)
        throw err("Failed to read fixed screen information from framebuffer file!");
    return f;
}

// Wait for vertical sync.
void Scr::vsync()
{
    if (CTL(FBIO_WAITFORVSYNC, 0) < 0)
        throw err("Failed to wait for vertical sync!");
}
