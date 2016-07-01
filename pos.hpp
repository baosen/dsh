#pragma once
#include "types.hpp"

class Pos {
public:
    Pos(const uint x, const uint y);
    uint i(const uint w) const;
private:
    const uint x, y;
    friend class Rect;
};
