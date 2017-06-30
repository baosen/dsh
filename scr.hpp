#pragma once
#include <linux/fb.h>

// Computer screen.
class Scr {
public:
    typedef fb_var_screeninfo varinfo;
    typedef fb_fix_screeninfo fixinfo;

    // Open framebuffer file.
    Scr();
    // Close framebuffer file.
    ~Scr();

    // Get variable screen info.
    varinfo vinfo();
    // Get fixed screen info.
    fixinfo finfo();

    // Wait for vertical sync.
    void vsync();
private:
    int fd;                      // Framebuffer file descriptor.
    uint w,                      // Width.
         h,                      // Height.
         bpp,                    // Bits per pixel.
         roff, goff, boff, aoff, // Offset to pixel in bits. Bitshift to reach it.
         rl, gl, bl, al;         // Length of pixel in bits.
    friend class Fb;
};

