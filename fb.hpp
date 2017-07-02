#pragma once
#include <memory>
#include "pos.hpp"
#include "rect.hpp"
#include "pix.hpp"
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
    void  set(const uint i, const Pix& c);

    // Copy provided buffer to this framebuffer.
    void  copy(const uint i, const char *buf, const size_t len);
    // Clear/blacken the entire screen.
    void  clear();

    // Get size in pixels of the framebuffer.
    size_t pixlen() const;
    // Get size in bytes of the framebuffer.
    size_t len() const;

    // Flip between buffers.
    void flip();

    // Bit offsets to the position of the color value.
    int   roff, // Red offset.
          goff, // Green offset.
          boff, // Blue offset.
          aoff; // Alpha offset.
private:
    void vsync();

    Scr   scr;  // The screen to grab the framebuffer.

    size_t size, // Size in bytes.
           plen; // Size in pixels.

    std::unique_ptr<u8[]> dbuf;    // Double buffer for tear-free framebuffer manipulation.
    bool                  vsyncen; // Is vertical sync enabled.

    u8*    fb;

    friend class Rect;
};
