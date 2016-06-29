#include "pix.hpp"

Pix(const uint r, const uint g, const uint b, const uint a) 
    : p((r << 32) | (g << 16) | (b << 8)) {}
