#include "rect.hpp"
#include "m.hpp"
#include "keywait.hpp"

// Test "hacky" mouse combined with window rectangle.
int main() 
{
    M m(1);
    int px = 0, py = 0;
    for (;;) {
        const auto e = m.rd();
        px += e.x;
        py += -1*e.y;
        if (px < 0)
            px = 0;
        if (py < 0)
            py = 0;
        Rect r(Pos(px, py), Res(100, 100));
        r.fill(Pix(255, 255, 255, 255));
    }
    return 0;
}
