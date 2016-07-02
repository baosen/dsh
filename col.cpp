#include "col.hpp"

Col::Col(const uint r, const uint g, const uint b) 
    : r(r), g(g), b(b) {}

u32 Col::val(const uint roff, const uint goff, const uint boff) const {
    // TODO: Check for overflow.
    return (r << roff) | (g << goff) | (b << boff);
}
