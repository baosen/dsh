#include "pos.hpp"

Pos::Pos(const uint x, const uint y)
    : x(x), y(y)
{}


uint Pos::i(const uint w) const {
    return x+y*w;
}
