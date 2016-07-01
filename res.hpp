#pragma once
#include "types.hpp"
class Rect;
class Res {
public:
    Res() : w(0), h(0) {}
    Res(const uint w, const uint h);

    uint getw() {
        if (!w)
            throw err("Width is null!");
        return w;
    }

    uint geth() {
        if (!h)
            throw err("Height is null!");
        return h;
    }
private:
    const uint w, h;
    friend class Rect;
};
