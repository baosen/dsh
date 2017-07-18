#include "res.hpp"
#include "err.hpp"

// Create empty resolution.
res::res() : w(0), h(0) {}

// Create resolution of width w and height h.
res::res(const uint w, const uint h) : w(w), h(h) 
{
    if (!w || !h)
        throw err("Resolution is zero!");
}

// Assign res r to this.
const res& res::operator=(const res& r) 
{
    w = r.w;
    h = r.h;
    return *this;
}
