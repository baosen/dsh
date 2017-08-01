#include <vector>
#include <cstring>
#include "wnd.hpp"
#include "m.hpp"
#include "keywait.hpp"
using namespace std;

// Test double flip and maximize window.
static void maxmintest()
{
    wnd r1(pos(400, 400), res(100, 100)),
        r2(pos(200, 200), res(100, 100));

    r1.fillflip(pix(255, 255, 255, 255));
    keywait();
    r2.fillflip(pix(255, 0, 255, 255));
    keywait();

    r2.max();
    r2.fillflip(pix(255, 0, 255, 255));
    keywait();

    r2.min();
    r2.fillflip(pix(255, 0, 255, 255));
    keywait();
}

// Fill window with red.
static void redfill(wnd& w, vector<u32>& v, const prop& cp)
{
    fill(begin(v), end(v), pix(255, 0, 0, 255).val(cp));
    w.write(v.data(), 0, v.size());
}

// Fill window with green.
static void greenfill(wnd& w, vector<u32>& v, const prop& cp)
{
    fill(begin(v), end(v), pix(0, 255, 0, 255).val(cp));
    w.write(v.data(), 0, v.size());
}

// Fill window with blue.
static void bluefill(wnd& w, vector<u32>& v, const prop& cp)
{
    // Fill with blue!
    fill(begin(v), end(v), pix(0, 0, 255, 255).val(cp));
    w.write(v.data(), 0, v.size());
}

// Test calling on wnd's write().
static void writetest()
{
    // Create window.
    wnd         w(pos(0, 0), res(100, 100));
    vector<u32> v(w.size());
    const auto  cp = w.cp();

    // Fill with red!
    greenfill(w, v, cp);
    keywait();

    // Fill with green!
    bluefill(w, v, cp);
    keywait();

    // Fill with blue!
    redfill(w, v, cp);
    keywait();
}

// Test moving the window.
static void movetest()
{
    m   m(1);
    int px = 0, // Current X position.
        py = 0; // Current Y position.

    wnd r(pos(px, py), res(100, 100));
    r.fillflip(pix(255, 255, 255, 255));

    for (;;) {
        const auto e = m.rd();
        px += e.x;
        py += -1*e.y;
        if (px < 0)
            px = 0;
        if (py < 0)
            py = 0;
        r.move(pos(px, py));
    }
}

// Test "hacky" mouse combined with window rectangle.
int main() 
{
    //maxmintest();
    //writetest();
    movetest();

    return EXIT_SUCCESS;
}
