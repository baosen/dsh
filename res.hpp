#pragma once
#include "types.hpp"

class res {
public:
    res();
    res(const uint w, const uint h);
    const res& operator=(const res& r);

    uint w, // Width of the resolution.
         h; // Height of the resolution.
};
