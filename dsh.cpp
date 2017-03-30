#include <iostream>
#include "types.hpp"
#include "fb.hpp"
#include "col.hpp"
#include "wnd.hpp"
#include "log.hpp"
using namespace std;

namespace {
    Col GREEN = Col(0, 255, 0);
    Wnd w1(Rect(Pos(0, 0), Res(100, 100)));
    Wnd w2(Rect(Pos(100, 100), Res(100, 100)));

    const char evtp[] = "/dev/input/event0"; // File path to the event-driven mouse device file.

    void draw() {
        w1.fill(GREEN);
        w2.fill(GREEN);
    }
}

int main() {
    Ms m(0);
    forever {
        const auto q = m.rd();
        for (const auto& e : q) {
            switch (e.type.m) {
            case In::MType::Left:
                cout << (e.val.min.left ? "left pressed!" : "left released!") << endl;
                break;
            case In::MType::Right:
                cout << (e.val.min.right ? "right pressed!" : "right released!") << endl;
                break;
            case In::MType::Mid:
                cout << (e.val.min.mid ? "middle pressed!" : "middle released!") << endl;
                break;
            case In::MType::Wheel:
                switch (e.val.min.wheel) {
                case In::Scr::UP:   // Scroll upwards.
                    cout << "Upward scroll!" << endl;
                    break;
                case In::Scr::DOWN: // Scroll downwards.
                    cout << "Downward scroll!" << endl;
                    break;
                }  
                break;
            case In::MType::X:
                cout << "x: " << e.val.min.x << endl;
                break;
            case In::MType::Y:
                cout << "y: " << e.val.min.y << endl;
                break;
            default:
                break;
            }
        }
    }
    return 0;
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
