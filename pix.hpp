#pragma once
#include "types.hpp"

// Offsets to the pixel bits.
struct off {
    int roff, // Red offset.
        goff, // Green offset.
        boff, // Blue offset.
        aoff; // Alpha offset.
};

// Colored screen pixel.
class pix {
public:
    pix(const uint r,  // Red.
        const uint g,  // Green.
        const uint b,  // Blue.
        const uint a); // Alpha.

    // Compute pixel formatted to the framebuffer's pixel format.
    u32 val(const int roff, // Red offset.
            const int goff, // Green offset.
            const int boff, // Blue offset.
            const int aoff) // Alpha offset.
            const;

    u32 val(const off& o) const;
private:
    uint r, // Red.
         g, // Green.
         b, // Blue.
         a; // Alpha-transparency.
};
