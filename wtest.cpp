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

    r1.fill(pix(255, 255, 255, 255));
    keywait();
    r2.fill(pix(255, 0, 255, 255));
    keywait();

    r2.max();
    r2.fill(pix(0, 0, 255, 255));
    keywait();
}

static void test2()
{
    wnd w(pos(0, 0), res(100, 100));
    w.fill(pix(255, 0, 255, 255));
    keywait();

    const auto  o = w.o();
    vector<u32> v(w.size());
    fill(begin(v), end(v), pix(255, 255, 255, 255).val(o));
    w.write(v.data(), 0, v.size());
}

static void movetest()
{
    m   m(1);
    int px = 0, 
        py = 0;

    wnd r(pos(px, py), res(100, 100));
    r.fill(pix(255, 255, 255, 255));

    for (;;) {
        const auto e = m.rd();
        px += e.x;
        py += -1*e.y;
        if (px < 0)
            px = 0;
        if (py < 0)
            py = 0;
        wnd r(pos(px, py), res(100, 100));
        try {
            r.fill(pix(255, 255, 255, 255));
        } catch (const err& e) {
            continue;
        }
    }
}

// Test "hacky" mouse combined with window rectangle.
int main() 
{
    //test1();
    //test2();
    movetest();

    return EXIT_SUCCESS;
}
