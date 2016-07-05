#pragma once
#include "types.hpp"
class Rect;
class Res {
public:
    Res();
    Res(const uint w, const uint h);

    Res& operator=(const Res& r) {
        w = r.w;
        h = r.h;
    }

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
    uint w, h;
    friend class Rect;
};
