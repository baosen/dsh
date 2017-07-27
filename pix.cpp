#include "pix.hpp"

// The color of a pixel.
pix::pix(const uint r, // Red.
         const uint g, // Green.
         const uint b, // Blue.
         const uint a) // Alpha.
    : r(r), // Red.
      g(g), // Green.
      b(b), // Blue.
      a(a)  // Alpha.
{}

// Compute pixel formatted to the framebuffer's pixel format.
u32 pix::val(const int roff, // Red bit position.
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

// Compute pixel formatted to the framebuffer's pixel format.
u32 pix::val(const prop& p) // Color properties.
             const
{
    u32 pix = 0;

    if (p.rlen > 0)
        pix |= r << p.roff;
    if (p.glen > 0)
        pix |= g << p.goff;
    if (p.blen > 0)
        pix |= b << p.boff;
    if (p.alen > 0)
        pix |= a << p.aoff;

    return pix;
}
