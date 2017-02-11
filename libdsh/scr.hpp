#pragma once
#include <linux/fb.h>

// Computer screen.
class Scr {
    int fd;                      // Framebuffer file descriptor.
    uint w,                      // Width.
         h,                      // Height.
         bpp,                    // Bits per pixel.
         roff, goff, boff, aoff, // Offset to pixel in bits. Bitshift to reach it.
         rl, gl, bl, al;         // Length of pixel in bits.

    friend class Fb;
public:
    typedef fb_var_screeninfo varinfo;
    typedef fb_fix_screeninfo fixinfo;

    Scr();
    ~Scr();

    // Get variable screen info.
    varinfo vinfo();
    // Get fixed screen info.
    fixinfo finfo();
};

