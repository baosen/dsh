#pragma once
#include "types.hpp"

// Position.
class Pos {
public:
    // Create blank position positioned at (0, 0).
    Pos();
    // Set x and y of position.
    Pos(const uint x, const uint y);

    uint i(const uint w) const;
    const Pos& operator=(const Pos&);

    uint x, y;
};
