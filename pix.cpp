#include "pix.hpp"

Pix::Pix(const u8 r, const u8 g, const u8 b) 
    : p(b | (g << 8) | (r << 16)) {}
