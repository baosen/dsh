#include "bg.hpp"

// Update background.
void bg::update()
{
    // Get screen resolution.
    scr s;
    auto v = s.vinfo();
    // Resize background to the current screen esolution.
    vec.resize(v.xres * v.yres);
}
