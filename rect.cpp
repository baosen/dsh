#include "rect.hpp"

Rect::Rect(const Pos& p, const Res& r)
    : p(p), r(r) {}

int Rect::i() const {
    return p.i(r.w);
}

size_t size() const {
    return r.h*r.w;
}
