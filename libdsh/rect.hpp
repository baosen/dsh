#pragma once
#include "pos.hpp"
#include "res.hpp"
#include "col.hpp"
#include "fb.hpp"

class Rect {
    Pos p;
    Res r;
    friend class Fb;
public:
    Rect();
    Rect(const Pos& p, const Res& r);
    uint   i()                        const;
    // Returns the rectangle area size.
    size_t size()                     const;
    void fill(Ptr& f, const Col& c) const;
};
