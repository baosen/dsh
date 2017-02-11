#include "rect.hpp"
#include "fb.hpp"

Rect::Rect(const Pos& p, const Res& r) : p(p), r(r) {}
Rect::Rect() {}

// Computes the index of its position in the framebuffer.
uint Rect::i() const {
    return p.i(r.w);
}

// Fill rectangle in framebuffer with the colour c.
void Rect::fill(const Col& c) const {
    Fb fb;

    // Compute pixel and position.
    const auto v = fb.scr.vinfo();
    const auto pix = c.val(v.red.offset, v.green.offset, v.blue.offset);
    const auto start = p.x + (p.y * r.w);

    // Fill!
    for (size_t i = 0; i < r.h; ++i)
        for (size_t j = 0; j < r.w; ++j)
            fb.get32(start+i) = pix;
}

size_t Rect::size() const {
    return r.h*r.w;
}
