#pragma once
#include "pos.hpp"
#include "res.hpp"
#include "col.hpp"
class Fb;
class Rect {
public:
    Rect(const Pos& p, const Res& r);
    uint i() const;
    size_t size() const;
    void fill(void* fb, const Col& c);
private:
    Pos p;
    Res r;

    friend class Fb;
};
