#include <iomanip>
#include "msys.hpp"
#include "evm.hpp"
#include "m.hpp"
#include "log.hpp"
#include "zero.hpp"
using namespace std;

// Mouse subsystem.
namespace {
    deque<msys::Ev> evq; // Queue of mouse events.

    // Key. Mouse button press or release.
    void key(msys::Ev& ev, const input_event& e) {
        switch (e.code) {
        case BTN_LEFT:    // Left mouse button.
            ev.type = msys::Ev::LEFT;
            ev.val = e.value;
            break;
        case BTN_RIGHT:   // Right mouse button.
            ev.type = msys::Ev::RIGHT;
            ev.val = e.value;
            break;
        case BTN_MIDDLE:  // Middle mouse button.
            ev.type = msys::Ev::MID;
            ev.val = e.value;
            break;
        case BTN_SIDE:    // Side mouse button.
            ev.type = msys::Ev::SIDE;
            ev.val = e.value;
            break;
        case BTN_EXTRA:   // Extra mouse button?
            ev.type = msys::Ev::EXTRA;
            ev.val = e.value;
            break;
        case BTN_FORWARD: // Forward button.
            ev.type = msys::Ev::FORWARD;
            ev.val = e.value;
            break;
        case BTN_BACK:    // Back button (to go backwards in browser?).
            ev.type = msys::Ev::BACK;
            ev.val = e.value;
            break;
        case BTN_TASK:    // Task button.
            ev.type = msys::Ev::TASK;
            ev.val = e.value;
            break;
        default:
            // Unknown.
            break;
        }
    }
    
    // Relative axis. Mouse movement.
    void rel(msys::Ev& ev, const input_event& e) {
        // Mouse movements follows top-left coordinate system, where origo is at the top left of the screen and the positive y-axis points downwards.
        switch (e.code) {
        case 0: // x-axis, - left, + right.
            ev.type = msys::Ev::X;
            ev.val = e.value;
            break;
        case 1: // y-axis, - upwards, + downwards.
            ev.type = msys::Ev::Y;
            ev.val = e.value;
            break;
        case 8: // wheel scroll, 1 up and -1 down.
            ev.type = msys::Ev::WHEEL;
            ev.val = e.value;
            break;
        }
    }
    
    // Synthetic. Handle synthetic events.
    bool syn(msys::Ev& ev, const __s32 code) {
        switch (code) {
        case SYN_REPORT:  // Reported event.
            return true;
        case SYN_DROPPED: // Dropped event.
            // TODO: Throw away all frames between the reports.
            break; 
        }
        return false;
    }
    
    // Fill in event based on its read type.
    bool fillevt(deque<msys::Ev>& d, const input_event& e) {
        msys::Ev ev;
        zero(ev);
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
            return syn(ev, e.code);
        default: {
            stringstream ss;
            ss << "Unknown type:" << hex << setw(2) << e.type << endl;
            throw err(ss.str().c_str());
                 }
        }
    }
}

// Window functions for event device mouse.
namespace evm {
    Evm e; // Event mouse device.

    // Open mouse event device.
    static bool init() {
        return false;
    }

    // Wait for event and get it.
    static void waitevt(char *buf, const size_t n) {
        msys::Ev mev;
        for (uint i = 0; i < n; ++i) {
            zero(mev);
            forever {
                const auto ev = e.rd();
                switch (ev.type) {
                case EV_REL: // Relative motion.
                    rel(mev, ev);
                    break;
                case EV_KEY: // Mouse button press and release.
                    key(mev, ev);
                    break;
                case EV_ABS: // Absolute motion.
                    // Absolute value to announce touch pad movement speed?
                    continue;
                case EV_MSC: // Miscellanous?
                    continue;
                case EV_SYN: // Synchronization events.
                    syn(mev, ev.code);
                    break;
                default: {   // Ignore unknown events.
                    continue;
                    //stringstream ss;
                    //ss << "Unknown type:" << hex << setw(2) << e.type << endl;
                    //throw err(ss.str().c_str());
                         }
                }
            }
            // Copy mouse event block over to the buffer.
            memcpy(buf, &mev, sizeof mev);
            // Go to next block in the buffer.
            buf = buf+sizeof(mev);
        }
    }
}

// Window functions for "hacky" device mouse.
namespace m {
    M m; // "Hacky" mouse.

    // Initialize and setup "hacky" mouse.
    static bool init() {
        return m.open(0);
    }

    // Wait for mouse motion event and get it.
    deque<msys::Ev> evq; // events that has not been given to the upper layer.
    static void waitevt(char *buf, const size_t n) {
        msys::Ev   mev;
        const auto ev = m.rd();
        // Add X-axis event.
        if (ev.x != 0) {
            zero(mev);
            mev.type = msys::Ev::X;
            mev.val  = ev.x;
            evq.push_back(mev);
        }
        // Add Y-axis event.
        if (ev.y != 0) {
            zero(mev);
            mev.type = msys::Ev::Y;
            mev.val  = ev.y;
            evq.push_back(mev);
        }
        // Add left button event.
        zero(mev);
        mev.type = msys::Ev::LEFT;
        mev.val  = ev.left;
        evq.push_back(mev);
        // Add middle button event.
        zero(mev);
        mev.type = msys::Ev::MID;
        mev.val  = ev.mid;
        evq.push_back(mev);
        // Add right button event.
        zero(mev);
        mev.type = msys::Ev::RIGHT;
        mev.val  = ev.right;
        evq.push_back(mev);
        // Copy the mouse events to the buffer.
        for (uint i = 0; i < n; ++i) {
            if (evq.empty())
                return;
            // Get mouse event from the front of the queue.
            mev = evq.front();
            memcpy(buf, &mev, sizeof mev);
            // Go to next block in the buffer.
            buf = buf+sizeof(mev);
            // Remove it from the front of the queue.
            evq.pop_front();
        }
    }
}

// Initialize mouse.
bool (*minit[])() {
    &evm::init, // Event mouse initialization.
    &m::init,   // "hacky" mouse initialization.
};

// Wait for event and get mouse motion.
static msys::Mmotion mot[] {
    &evm::waitevt, // Get event mouse motion.
    &m::waitevt    // Get "hacky" mouse motion.
};

// Current mouse device that is used.
msys::Mmotion msys::devmot = nullptr;

// Initialize and setup mouse.
void msys::init() {
    using namespace msys;

    // Find and initialize an available mouse.
    for (uint i = 0; i < sizeof(minit); ++i) {
        // Try initializing the mouse.
        if (minit[i]()) {
            // Set its function to get the position of the mouse.
            msys::devmot = mot[i];
            break;
        }
    }
    if (!msys::devmot)
        die("Failed to find a mouse on the system!");
}
