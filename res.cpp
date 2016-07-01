#include "res.hpp"
#include "err.hpp"
Res::Res(const uint w, const uint h)
    : w(w), h(h) {
    if (!w || !h)
        throw err("Resolution is zero!");
}
