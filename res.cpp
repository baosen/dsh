#include "res.hpp"
#include "err.hpp"

// Create empty resolution.
Res::Res() : w(0), h(0) {}

// Create resolution of width w and height h.
Res::Res(const uint w, const uint h) : w(w), h(h) {
    if (!w || !h)
        throw err("Resolution is zero!");
}

// Assign res r to this.
const Res& Res::operator=(const Res& r) {
    w = r.w;
    h = r.h;
    return *this;
}
