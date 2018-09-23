#pragma once
#include "types.hpp"

// Resolution
class res {
public:
    // Construct empty resolution.
    res();
    // Construct resolution of width w and height h.
    res(const uint w, const uint h);

    // Assign existing resolution to this object.
    const res& operator=(const res& r);

    uint w, // Width of the resolution.
         h; // Height of the resolution.
};
