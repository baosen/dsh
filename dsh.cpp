#include <iostream>
#include <algorithm>
#include "err.hpp"
#include "types.hpp"
#include "fb.hpp"
#include "col.hpp"
#include "wnd.hpp"
using namespace std;

int main() {
    try {
        Wnd w1(Rect(Pos(100, 200), Res(100, 100)), Col(0, 0, 255));
        Wnd w2(Rect(Pos(200, 300), Res(100, 100)), Col(0, 0, 255));
        Wnd w3(Rect(Pos(300, 400), Res(100, 100)), Col(0, 0, 255));
        Wnd w4(Rect(Pos(400, 500), Res(100, 100)), Col(0, 0, 255));
        //Fb fb;
        //for (int i = 0; i < 5; i++) {
        //    fb.fill(Rect(Pos(100+(i*100), 100), Res(100, 100)), Col(255, 0, 0));
        //    fb.fill(Rect(Pos(100+(i*100), 200), Res(100, 100)), Col(0, 255, 0));
        //    fb.fill(Rect(Pos(100+(i*100), 300), Res(100, 100)), Col(0, 0, 255));
        //    fb.fill(Rect(Pos(100+(i*100), 400), Res(100, 100)), Col(0, 255, 255));
        //}
    } catch (const Err& e) {
        cerr << "Error code: " << hex << scast<int>(e) << endl;
    } catch (const err& e) {
        cerr << e << endl;
    }
    return 0;
}
