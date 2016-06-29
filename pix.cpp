#include "pix.hpp"

Pix::Pix(const uint r, const uint g, const uint b, const uint a) 
    : p((r << 31) | (g << 15) | (b << 7) | a) {}
