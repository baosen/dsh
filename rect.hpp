#pragma once
#include "pos.hpp"
#include "res.hpp"
#include "col.hpp"
#include "fb.hpp"
class Rect {
public:
    Rect(const Pos& p, const Res& r);
    uint i() const;
    size_t size() const;
    void fill(Fb& fb, const Col& c) const;
private:
    Pos p;
    Res r;
    friend class Fb;
};
