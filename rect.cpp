#include "rect.hpp"
#include "fb.hpp"

// Create an empty rectangle in the framebuffer.
Rect::Rect() {}

// Create a rectangle in the framebuffer.
Rect::Rect(const Pos& p, // The position to place the rectangle in the framebuffer.
           const Res& r) // The resolution of the rectangle in the framebuffer.
    : p(p), r(r) {}

// Computes the index of its position in the framebuffer.
uint Rect::i() const {
    return p.i(r.w);
}

// Fill rectangle in framebuffer with the colour c.
void Rect::fill(const Col& c) // Colour to fill the inside of the rectangle with.
                const 
{
    // Open framebuffer.
    Fb fb;

    // Compute pixel color and position.
    const auto v   = fb.scr.vinfo();
    const auto pix = c.val(v.red.offset, v.green.offset, v.blue.offset);
    const auto s   = p.x + p.y * v.xres;

    // Fill the rectangle in Linux framebuffer.
    for (size_t y = 0; y < r.h; ++y)
        for (size_t x = 0; x < r.w; ++x)
            fb.get32(s+x+(y*v.xres)) = pix;
}

// Get the size of the rectangle.
size_t Rect::size() const 
{
    return r.h*r.w;
}

// Resize the rectangle image in the framebuffer.
void Rect::resize(const uint w, const uint h) 
{
    r.w = w;
    r.h = h;
}

// Maximize the rectangle to fill the screen.
void Rect::max() 
{
    // Open framebuffer.
    Fb         fb;
    // Resize the rectangle to fill the entire screen.
    const auto v = fb.scr.vinfo();
    resize(v.xres, v.yres);
}
