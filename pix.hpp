#pragma once
#include "types.hpp"
class Fb;
class Pix {
public:
    Pix(const u8 r, const u8 g, const u8 b);
private:
    u32 p;
    friend class Fb;
};
