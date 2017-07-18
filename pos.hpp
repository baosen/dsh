#pragma once
#include "types.hpp"

// Position.
class pos {
public:
    // Create blank position positioned at (0, 0).
    pos();
    // Set x and y of position.
    pos(const uint x, const uint y);

    // Get index computed from width.
    uint               i(const uint stride) const;
    // Assign position.
    const pos& operator=(const pos&);

    uint x, y;
};
