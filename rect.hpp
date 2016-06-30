#pragma once
#include "pos.hpp"
#include "res.hpp"

class Rect {
public:
    Rect(const Pos& p, const Res& r);
    uint i() const;
    size_t size() const;
private:
    Pos p;
    Res r;
};
