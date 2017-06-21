#include "col.hpp"

// Colour pixel.
Col::Col(const uint r, // Red.
         const uint g, // Green.
         const uint b, // Blue.
         const uint a) // Alpha.
    : r(r), g(g), b(b), a(a) {}

// Get pixel formatted to framebuffer's pixel format.
u32 Col::val(const uint roff, // Red bit position.
             const uint goff, // Green bit position.
             const uint boff, // Blue bit position.
             const uint aoff) // Alpha-transparency bit position.
             const 
{
    return r << roff | g << goff | b << boff | a << aoff;
}
