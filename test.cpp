#include "ms.hpp"
#include "types.hpp"

void testms() {
    Ms m;
    forever {
        m.read();
    }
}

void testfb() {
    Fb fb;
    for (int i = 0; i < 5; i++) {
        fb.fill(Rect(Pos(100+(i*100), 100), Res(100, 100)), Col(255, 0, 0));
        fb.fill(Rect(Pos(100+(i*100), 200), Res(100, 100)), Col(0, 255, 0));
        fb.fill(Rect(Pos(100+(i*100), 300), Res(100, 100)), Col(0, 0, 255));
        fb.fill(Rect(Pos(100+(i*100), 400), Res(100, 100)), Col(0, 255, 255));
    }
}

int main() {
    return 0;
}
