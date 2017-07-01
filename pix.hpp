#pragma once
#include "types.hpp"

// Colored pixel.
class Pix {
public:
    Pix(const uint r,  // Red.
        const uint g,  // Green.
        const uint b,  // Blue.
        const uint a); // Alpha.

    // Compute pixel formatted to the framebuffer's pixel format.
    u32 val(const int roff, // Red offset.
            const int goff, // Green offset.
            const int boff, // Blue offset.
            const int aoff) // Alpha offset.
            const;
private:
    uint r, // Red.
         g, // Green.
         b, // Blue.
         a; // Alpha-transparency.
};
