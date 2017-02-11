#include "rect.hpp"

Rect::Rect(const Pos& p, const Res& r) : p(p), r(r) {}
Rect::Rect() {}

// Computes the index of its position in the framebuffer.
uint Rect::i() const {
    return p.i(r.w);
}

// Fill rectangle in framebuffer with the colour c.
void Rect::fill(Scr& s, const Col& c) const {
    const auto x = c.val(s.roff, s.boff, s.goff);
    const auto start = p.x+(p.y*f.w);
    for (size_t row = 0; row < r.h; ++row)
        for (size_t col = 0; col < r.w; ++col)
            *((rcast<u32*>(s.fb))+start+col+(row*f.w)) = x;
}

size_t Rect::size() const {
    return r.h*r.w;
}
