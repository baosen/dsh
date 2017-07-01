#pragma once
#include <linux/fb.h>

// Double-buffered framebuffer screen.
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
    // Pan display.
    void pan(const Scr::varinfo& v);

    // Flip to another buffer.
    void flip();
private:
    int fd;                      // Framebuffer file descriptor.

         // Resolution:
    uint w,                      // Width.
         h,                      // Height.
         bpp,                    // Bits per pixel.

         // Pixel offsets:
         roff, goff, boff, aoff, // Offset to pixel in bits. Bitshift to reach it.

         // Pixel length:
         rl,                     // Length of red pixel in bits.
         gl,                     // Length of green pixel in bits.
         bl,                     // Length of blue pixel in bits.
         al,                     // Length of alpha pixel in bits.
         page;                   // Current buffer page.

    varinfo v;

    friend class Fb;
};
