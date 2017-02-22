#include "rect.hpp"
#include "fb.hpp"

// Create an empty rectangle in the framebuffer.
Rect::Rect() {}

// Create a rectangle in the framebuffer.
Rect::Rect(const Pos& p, const Res& r) : p(p), r(r) {}

// Computes the index of its position in the framebuffer.
uint Rect::i() const {
    return p.i(r.w);
}

// Fill rectangle in framebuffer with the colour c.
void Rect::fill(const Col& c) const {
    // Open framebuffer.
    Fb fb;

    // Compute pixel color and position.
    const auto v = fb.scr.vinfo();
    const auto pix = c.val(v.red.offset, v.green.offset, v.blue.offset);
    const auto s = p.x + (p.y * v.xres);

    // Fill!
    for (size_t y = 0; y < r.h; ++y)
        for (size_t x = 0; x < r.w; ++x)
            fb.get32(s+x+(y*v.xres)) = pix;
}

size_t Rect::size() const {
    return r.h*r.w;
}
