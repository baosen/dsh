#include "rect.hpp"

Rect::Rect(const Pos& p, const Res& r)
    : p(p), r(r) {}

// Computes the index of its position in the framebuffer.
int Rect::i() const {
    return p.i(r.w);
}

size_t Rect::size() const {
    return r.h*r.w;
}
