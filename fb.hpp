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

    // Get size in bytes of the framebuffer.
    size_t len() const;

    Scr    scr;  // The screen to grab the framebuffer.
    uint   roff, // Red offset.
           goff, // Green offset.
           boff, // Blue offset.
           aoff; // Alpha offset.
private:
    size_t size;
    u8*    fb;

    friend class Rect;
};
