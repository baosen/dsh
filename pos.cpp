#include "pos.hpp"

// Create blank position positioned at (0, 0).
Pos::Pos() : x(0), y(0) {}

Pos::Pos(const uint x, const uint y)
    : x(x), y(y)
{}


uint Pos::i(const uint w) const {
    return x+y*w;
}

const Pos& Pos::operator=(const Pos& p) {
    x = p.x;
    y = p.y;
    return *this;
}
