#include "col.hpp"

Col::Col(const uint r, const uint g, const uint b, const uint a) 
    : r(r), g(g), b(b), a(a) {}

u32 Col::val(const uint roff, const uint goff, const uint boff, const uint aoff) const {
    return r << roff | g << goff | b << boff | a << aoff;
}
