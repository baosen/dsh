#pragma once
#include "pos.hpp"
#include "res.hpp"

class Rect {
public:
    Rect(const Pos& p, const Res& r)
        : p(p), r(r) {}

    int i() const {
        return p.i(r.w);
    }

    size_t size() const {
        return r.h*r.w;
    }
private:
    Pos p;
    Res r;
};
