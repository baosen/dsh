#include "col.hpp"

Col::Col(const u8 r, const u8 g, const u8 b) 
    : r(r), g(g), b(b) {}

u32 Col::val(const uint roff, const uint goff, const uint boff) const {
    return (r << roff) | (g << goff) | (b << boff);
}
