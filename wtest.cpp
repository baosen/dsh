#include <vector>
#include <cstring>
#include "wnd.hpp"
#include "m.hpp"
#include "keywait.hpp"
using namespace std;

static void test1()
{
    wnd r1(pos(400, 400), res(100, 100)),
        r2(pos(200, 200), res(100, 100));

    r1.fillflip(pix(255, 255, 255, 255));
    keywait();
    r2.fillflip(pix(255, 0, 255, 255));
    keywait();

    r2.max();
    r2.fillflip(pix(0, 0, 255, 255));
    keywait();
}

// Test calling on wnd's write().
static void wndwrittest()
{
    // Create window.
    wnd w(pos(0, 0), res(100, 100));

    // Fill with blue!
    const auto  cp = w.cp();
    vector<u32> v(w.size());
    fill(begin(v), end(v), pix(0, 0, 255, 255).val(cp));
    w.write(v.data(), 0, v.size());
    keywait();

    // Fill with red!
    fill(begin(v), end(v), pix(255, 0, 0, 255).val(cp));
    w.write(v.data(), 0, v.size());
    keywait();

    // Fill with green!
    fill(begin(v), end(v), pix(0, 255, 0, 255).val(cp));
    w.write(v.data(), 0, v.size());
    keywait();
}

// Test moving the window.
static void movetest()
{
    m   m(1);
    int px = 0, 
        py = 0;

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
    //test1();
    wndwrittest();
    //movetest();

    return EXIT_SUCCESS;
}
