#pragma once
#include "pos.hpp"
#include "rect.hpp"
#include "col.hpp"
#include "scr.hpp"

// Framebuffer.
class Fb {
public:
    // Grab framebuffer.
    Fb();
    // Release framebuffer.
    ~Fb();

    // Get 32-bit color value from the framebuffer memory.
    u8&   get8(const uint i);
    u32&  get32(const uint i);

    // Set color value in the framebuffer.
    void  set(const uint i, const Col& c);
    // Fill a box in the framebuffer.
    void  boxfill(const char *buf, const uint w, const uint h);
    void  rowfill(const char *buf, const uint row, const uint len);

    // Get size in pixels of the framebuffer.
    size_t pixlen() const;
    // Get size in bytes of the framebuffer.
    size_t len() const;

    Scr   scr;  // The screen to grab the framebuffer.

    // Bit offsets to the position of the color value.
    int   roff, // Red offset.
          goff, // Green offset.
          boff, // Blue offset.
          aoff; // Alpha offset.
private:
    size_t size, // Size in bytes.
           plen; // Size in pixels.

    u8*    fb;

    friend class Rect;
};
