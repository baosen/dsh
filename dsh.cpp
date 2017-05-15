// dsh: Shell for desktops.
#include <cstring>
#include "wnd.hpp"
#include "log.hpp"
#include "m.hpp"
#include "kbsys.hpp"
#include "evm.hpp"
#include "msys.hpp"
#include "net.hpp"
using namespace std;

namespace {
    Col GREEN = Col(0, 255, 0);
    Wnd w1(Rect(Pos(0, 0), Res(100, 100)));
    Wnd w2(Rect(Pos(100, 100), Res(100, 100)));
}

/*
// Mouse button press or release.
static void key(In::Ev& ev, input_event& e) {
    switch (e.code) {
    case BTN_LEFT:    // Left mouse button.
        ev.type.m = In::MType::Left;
        ev.val.min.left = e.value;
        break;
    case BTN_RIGHT:   // Right mouse button.
        ev.type.m = In::MType::Right;
        ev.val.min.right = e.value;
        break;
    case BTN_MIDDLE:  // Middle mouse button.
        ev.type.m = In::MType::Mid;
        ev.val.min.mid = e.value;
        break;
    case BTN_SIDE:    // Side mouse button.
        ev.type.m = In::MType::Side;
        ev.val.min.side = e.value;
        break;
    case BTN_EXTRA:   // Extra mouse button?
        ev.type.m = In::MType::Extra;
        ev.val.min.extra = e.value;
        break;
    case BTN_FORWARD: // Forward button.
        ev.type.m = In::MType::Forward;
        ev.val.min.forward = e.value;
        break;
    case BTN_BACK:    // Back button (to go backwards in browser?).
        ev.type.m = In::MType::Back;
        ev.val.min.back = e.value;
        break;
    case BTN_TASK:    // Task button.
        ev.type.m = In::MType::Task;
        ev.val.min.task = e.value;
        break;
    default:
        break;
    }
}

// Mouse movement.
static void rel(In::Ev& ev, input_event& e) {
    // Mouse movements follows top-left coordinate system, where origo is at the top left of the screen and the positive y-axis points downwards.
    switch (e.code) {
    case 0: // x-axis, - left, + right.
        ev.type.m = In::MType::X;
        ev.val.min.x = e.value;
        break;
    case 1: // y-axis, - upwards, + downwards.
        ev.type.m = In::MType::Y;
        ev.val.min.y = e.value;
        break;
    case 8: // wheel scroll.
        ev.type.m = In::MType::Wheel;
        ev.val.min.wheel = e.value;
        break;
    }
}

// Handle synthetic events.
static bool syn(deque<In::Ev>& d, In::Ev& ev, const __s32 code) {
    switch (code) {
    case SYN_REPORT:
        return true;
    case SYN_DROPPED: // Oh snap!
        break; // TODO: Throw away all frames between the reports.
    }
    return false;
}

// Fill in event based on its read type.
static bool fill(deque<In::Ev>& d, input_event& e) {
    In::Ev ev;
    zero(ev);
    ev.d = In::Dev::Mouse;
    switch (e.type) {
    case EV_REL: // Relative motion.
        rel(ev, e);
        d.push_back(ev);
        return false;
    case EV_KEY: // Mouse button press and release.
        key(ev, e);
        d.push_back(ev);
        return false;
    case EV_ABS: // Absolute motion.
        // Absolute value to announce touch pad movement speed?
        return false;
    case EV_MSC: // Miscellanous?
        return false;
    case EV_SYN: // Synchronization events.
        return syn(d, ev, e.code);
    default: {
        stringstream ss;
        ss << "Unknown type:" << hex << setw(2) << e.type << endl;
        throw err(ss.str().c_str());
             }
    }
}

int main2() {
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
*/

// Convert "hacky" mouse event to position.
static Pos topos(const M::Ev& e) {
    return Pos(e.x, e.y);
}

namespace {
    // Enable network capabilities.
    bool enable_net = false;
}

// Initialize window system.
static void init() {
    // Setup mouse.
    initm();
    // Setup keyboard.
    initkb();
    // Setup network.
    if (enable_net) {
        //initnet();
    }
}

// Server.
int main(const int argc, const char *argv[]) {
    // If argument provided.
    for (int i = 1; i < argc; ++i)
        if (!strcmp(argv[i], "-net"))
            enable_net = true;
    try {
        // Initialize window system.
        init();
        // Listen and respond to window commands.
        forever {
            const auto pos = mcurpos();
        }
        return EXIT_SUCCESS;
    } catch (const int c) {
        die(c);
    } catch (const err& e) {
        error(e);
    }
    return EXIT_FAILURE;
}
