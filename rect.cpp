#include "rect.hpp"

Rect::Rect() {}
Rect::Rect(const Pos& p, const Res& r) : p(p), r(r) {}

// Computes the index of its position in the framebuffer.
uint Rect::i() const {
    return p.i(r.w);
}

void Rect::fill(Fb& f, const Col& c) const {
    const auto x = c.val(f.roff, f.boff, f.goff);
    const auto start = p.x+(p.y*f.w);
    for (size_t row = 0; row < r.h; ++row)
        for (size_t col = 0; col < r.w; ++col)
            *(((u32*)f.fb)+start+col+(row*f.w)) = x;
}

size_t Rect::size() const {
    return r.h*r.w;
}
