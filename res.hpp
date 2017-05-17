#pragma once
#include "types.hpp"

class Rect;

class Res {
public:
    Res();
    Res(const uint w, const uint h);
    const Res& operator=(const Res& r);

    uint w, // width.
         h; // height.
};
