#include "pos.hpp"

// Create blank position positioned at (0, 0).
Pos::Pos() : x(0), y(0) {}

// Set x and y of position.
Pos::Pos(const uint x, const uint y)
    : x(x), y(y)
{}

// Get index computed from width.
uint Pos::i(const uint stride) // stride.
            const 
{
    return x+y*stride;
}

const Pos& Pos::operator=(const Pos& p) {
    x = p.x;
    y = p.y;
    return *this;
}
