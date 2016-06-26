#pragma once
#include "types.hpp"

class Pos {
public:
    Pos(const uint x, const uint y);

    int i(const int w) const {
        return x+y*w;
    }
private:
    const uint x, y;
};
