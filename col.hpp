#pragma once
#include "types.hpp"

class Fb;

class Col {
public:
    Col(const uint r, const uint g, const uint b, const uint a);
    u32 val(const uint roff, const uint goff, const uint boff, const uint aoff) const;
private:
    uint r, // Red.
         g, // Green.
         b; // Blue.
         a; // Alpha-transparency.
    friend class Fb;
};
