#pragma once
#include "types.hpp"

class Pos {
public:
    Pos();
    Pos(const uint x, const uint y);
    uint i(const uint w) const;
    const Pos& operator=(const Pos&);
private:
    uint x, y;
    friend class Rect;
};
