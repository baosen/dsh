#include <vector>
#include <cstring>
#include "wnd.hpp"
#include "m.hpp"
#include "keywait.hpp"
using namespace std;

static void test1()
{
    Wnd r1(Pos(400, 400), Res(100, 100)),
        r2(Pos(200, 200), Res(100, 100));

    r1.fill(Pix(255, 255, 255, 255));
    keywait();
    r2.fill(Pix(255, 0, 255, 255));
    keywait();

    r2.max();
    r2.fill(Pix(0, 0, 255, 255));
    keywait();
}

static void test2()
{
    Wnd w(Pos(0, 0), Res(100, 100));
    w.fill(Pix(255, 0, 255, 255));
    keywait();

    const auto  o = w.off();
    vector<u32> v(w.size());
    fill(begin(v), end(v), Pix(255, 255, 255, 255).val(o));
    w.write((byte*)v.data(), 0, v.size()*sizeof(u32));
}

static void movetest()
{
    M   m(1);
    int px = 0, 
        py = 0;

    Wnd r(Pos(px, py), Res(100, 100));
    r.fill(Pix(255, 255, 255, 255));

    for (;;) {
        const auto e = m.rd();
        px += e.x;
        py += -1*e.y;
        if (px < 0)
            px = 0;
        if (py < 0)
            py = 0;
        Wnd r(Pos(px, py), Res(100, 100));
        r.fill(Pix(255, 255, 255, 255));
    }
}

// Test "hacky" mouse combined with window rectangle.
int main() 
{
    //test1();
    test2();

    return EXIT_SUCCESS;
}
