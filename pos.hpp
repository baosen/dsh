#pragma once
#include "types.hpp"

// Position.
class Pos {
public:
    Pos();
    // Set x and y of position.
    Pos(const uint x, const uint y);
    uint i(const uint w) const;
    const Pos& operator=(const Pos&);
private:
    uint x, y;
    friend class Fbrect;
    friend class Wnd;
};
