#include "pos.hpp"

// Create blank position positioned at (0, 0).
pos::pos() : x(0), y(0) {}

// Set x and y of position.
pos::pos(const uint x, const uint y)
    : x(x), y(y)
{}

// Get index computed from width.
uint pos::i(const uint stride) // stride.
            const 
{
    return x + (y * stride);
}

// Assign (x, y)-position.
const pos& pos::operator=(const pos& p) // Position to assign.
{
    // Copy the coordinates over to this object.
    x = p.x;
    y = p.y;

    // Return this object.
    return *this;
}
