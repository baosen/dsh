#include "libdsh/wnd.hpp"
#include "libdsh/log.hpp"
using namespace std;

namespace {
    Col GREEN = Col(0, 0, 255);
    Wnd w1(Rect(Pos(100, 200), Res(100, 100)));
    Wnd w2(Rect(Pos(200, 300), Res(200, 200)));
    Wnd w3(Rect(Pos(300, 400), Res(300, 300)));
    Wnd w4(Rect(Pos(400, 500), Res(400, 400)));
    void draw() {
        w1.fill(GREEN);
    }
}

int main() {
    try {
        draw();
        return 0;
    } catch (const int c) {
        die(c);
    } catch (const err& e) {
        error(e);
    }
    return 1;
}
