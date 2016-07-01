#pragma once
#include "types.hpp"
class Rect;
class Res {
public:
    Res(const uint w, const uint h);
private:
    const uint w, h;
    friend class Rect;
};
