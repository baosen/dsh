#include "pix.hpp"

// The color of a pixel.
Pix::Pix(const uint r, // Red.
         const uint g, // Green.
         const uint b, // Blue.
         const uint a) // Alpha.
    : r(r), g(g), b(b), a(a) {}

// Compute pixel formatted to the framebuffer's pixel format.
u32 Pix::val(const int roff, // Red bit position.
             const int goff, // Green bit position.
             const int boff, // Blue bit position.
             const int aoff) // Alpha-transparency bit position.
             const 
{
    u32 pix = 0;
    if (roff >= 0)
        pix |= r << roff;
    if (goff >= 0)
        pix |= g << goff;
    if (boff >= 0)
        pix |= b << boff;
    if (aoff >= 0)
        pix |= a << aoff;
    return pix;
}

u32 Pix::val(const Off& o) const
{
    u32 pix = 0;
    if (o.roff >= 0)
        pix |= r << o.roff;
    if (o.goff >= 0)
        pix |= g << o.goff;
    if (o.boff >= 0)
        pix |= b << o.boff;
    if (o.aoff >= 0)
        pix |= a << o.aoff;
    return pix;
}
