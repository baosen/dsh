#pragma once
#include "types.hpp"
class Fb;
class Pix {
public:
    Pix(const u8 r, const u8 g, const u8 b);
    u32 val(const uint roff, const uint goff, const uint boff) const;
private:
    uint r,g,b;
    friend class Fb;
};
