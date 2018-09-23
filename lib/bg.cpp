#include "bg.hpp"
#include "scr.hpp"

// Create background window.
bg::bg()
{
    scr        s;
    const auto v = s.vinfo();
    pcur = pos(0, 0);
    rcur = res(v.xres, v.yres);
    fill(pix(0, 0, 100, 255));
}
