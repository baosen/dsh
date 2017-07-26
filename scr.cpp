#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include "log.hpp"
#include "scr.hpp"
using namespace std;

// Control framebuffer screen.
#define CTL(req, ...) ioctl(fd, req, __VA_ARGS__)

// Setup double-buffered framebuffer screen.
scr::scr() 
    : page(0),     // Start on page buffer 0.
      pageen(true) // Enable double page buffers by default.
{
    // Open the framebuffer file.
    fd = ::open("/dev/fb0", O_RDWR);
    if (fd < 0)
        throw err("Cannot open /dev/fb0!");

    // Get variable screen information.
    v = vinfo();

    // Report screen attributes.
#ifdef DEBUG
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

    // Setup double buffer by doubling the height of the virtual screen.
    v.xres_virtual = v.xres;
    v.yres_virtual = v.yres * 2; // Double the height to have two buffers to flip between.
    v.width        = v.xres;
    v.height       = v.yres;
    v.xoffset      = v.yoffset = 0;
    if (CTL(FBIOPUT_VSCREENINFO, &v) < 0) {
#ifdef DEBUG
        syserror("Failed to setup double buffering!");
#endif
        pageen = false;
    }
}

// Close framebuffer file.
scr::~scr() 
{
    if (close(fd) < 0)
        die("Failed to close /dev/fb0!");
}

// Returns framebuffer variable screen info.
scr::varinfo scr::vinfo() 
{
    varinfo v;

    if (CTL(FBIOGET_VSCREENINFO, &v) < 0)
        throw err("Failed to read video screen information from framebuffer file!");

    return v;
}

// Returns framebuffer fixed screen info.
scr::fixinfo scr::finfo() 
{
    fixinfo f;

    if (CTL(FBIOGET_FSCREENINFO, &f) < 0)
        throw err("Failed to read fixed screen information from framebuffer file!");

    return f;
}

// Wait for vertical sync.
void scr::vsync()
{
    if (CTL(FBIO_WAITFORVSYNC, 0) < 0) {
#ifdef DEBUG
#   define ERRMSG "Failed to wait for vertical synchronization!";
        syserror(ERRMSG);
        throw err(ERRMSG);
#endif
        // TODO: Notify that vertical sync does not work using its own class.
    }
}

// Check for vertical sync by waiting for it.
bool scr::isvsync()
{
    return CTL(FBIO_WAITFORVSYNC, 0) >= 0;
}

// Pan display.
void scr::pan(const scr::varinfo& v) 
{
    if (CTL(FBIOPAN_DISPLAY, v) < 0)
        throw err("Failed to pan display!");
}

// Flip to another buffer.
void scr::flip()
{
    page = (page + 1) % 2;
    v.yoffset = page * v.yres;
}
