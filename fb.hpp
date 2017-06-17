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

    // Access its memory.
    u8&   get8(const uint i);
    u32&  get32(const uint i);

    Scr    scr; // The screen to grab the framebuffer.
private:
    size_t size;
    u8*    fb;

    friend class Rect;
};
