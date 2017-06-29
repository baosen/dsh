#pragma once
#include "types.hpp"

// Pixel color.
class Col {
public:
    Col(const uint r,  // Red.
        const uint g,  // Green.
        const uint b,  // Blue.
        const uint a); // Alpha.

    // Compute pixel formatted to the framebuffer's pixel format.
    u32 val(const uint roff, // Red offset.
            const uint goff, // Green offset.
            const uint boff, // Blue offset.
            const uint aoff) // Alpha offset.
            const;
private:
    uint r, // Red.
         g, // Green.
         b, // Blue.
         a; // Alpha-transparency.
};
