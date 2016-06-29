#include "pix.hpp"

Pix::Pix(const uint r, const uint g, const uint b, const uint a) 
    : p((a << 31) | (b << 15) | (g << 7) | r) {}
