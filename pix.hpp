#pragma once
#include "types.hpp"
class Fb;
class Pix {
public:
    Pix(const uint r, const uint g, const uint b, const uint a);
private:
    u32 p;
    friend class Fb;
};
