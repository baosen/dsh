#pragma once
#include "types.hpp"

// Color properties.
struct prop {
    // Length.
    int rlen, // Number of bits in red color.
        glen, // Number of bits in green color.
        blen, // Number of bits in blue color.
        alen; // Number of bits in alpha color.

    // Offsets to the pixel bits.
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

    u32 val(const prop& o) const;
private:
    uint r, // Red.
         g, // Green.
         b, // Blue.
         a; // Alpha-transparency.
};
