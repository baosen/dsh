#include <iomanip>
#include "msys.hpp"
#include "evm.hpp"
#include "m.hpp"
#include "log.hpp"
#include "zero.hpp"
using namespace std;

// Mouse subsystem.
static deque<msys::Ev> evq; // Stored queue of mouse events.

// Key. Mouse button press or release.
static void key(msys::Ev&          ev, // Mouse subsystem mouse event to set.
                const input_event& e)  // Event mouse device file event.
{
    switch (e.code) {
    case BTN_LEFT:    // Left mouse button.
        ev.type = msys::Ev::LEFT;
        ev.val  = e.value;
        break;
    case BTN_RIGHT:   // Right mouse button.
        ev.type = msys::Ev::RIGHT;
        ev.val  = e.value;
        break;
    case BTN_MIDDLE:  // Middle mouse button.
        ev.type = msys::Ev::MID;
        ev.val  = e.value;
        break;
    case BTN_SIDE:    // Side mouse button.
        ev.type = msys::Ev::SIDE;
        ev.val  = e.value;
        break;
    case BTN_EXTRA:   // Extra mouse button?
        ev.type = msys::Ev::EXTRA;
        ev.val  = e.value;
        break;
    case BTN_FORWARD: // Forward button.
        ev.type = msys::Ev::FORWARD;
        ev.val  = e.value;
        break;
    case BTN_BACK:    // Back button (to go backwards in browser?).
        ev.type = msys::Ev::BACK;
        ev.val  = e.value;
        break;
    case BTN_TASK:    // Task button.
        ev.type = msys::Ev::TASK;
        ev.val  = e.value;
        break;
    default:
        // Unknown event code.
        break;
    }
}

// Relative axis. Mouse movement.
void rel(msys::Ev&          ev, // Mouse subsystem mouse event to set.
         const input_event& e)  // Mouse input event.
{
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

// Handle synthetic events.
static bool syn(msys::Ev&   ev,   // Synthetic event.
                const __s32 code) // Code reported.
{
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
static bool fillevt(deque<msys::Ev>&   d, // Mouse subsystem event to set.
                    const input_event& e) // Event mouse device file.
{
    // Zero out event to put into the queue.
    msys::Ev ev;
    zero(ev);

    // Check what kind of type was given.
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

// Window functions for event device mouse.
namespace evm {
    Evm e; // Event mouse device.

    // Open mouse event device.
    static bool init() 
    {
        return e.open(0);
    }

    // Deinitialize event device mouse file.
    static void deinit() 
    {
        e.close();
    }

    // Wait for event and get it.
    static uint waitevt(void        *buf, // Buffer to put event blocks.
                        const size_t n)   // Number of blocks to put in the buffer.
    {
        msys::Ev mev;

        // Put n blocks into the buffer.
        for (uint i = 0; i < n; ++i) {
            // Reset and re-use mouse event.
            zero(mev);

            // Read input and handle it.
            forever {
                // Read event input.
                const auto ev = e.rd();

                // Check event type and handle accordingly.
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
                default: {   // Log and ignore unknown events.
                    // Warn user about the unknown event.
                    stringstream ss;
                    ss << "Unknown type:" << hex << setw(2) << ev.type << endl;
                    warn(ss.str());
                    continue;
                         }
                }
            }

            // Copy mouse event block over to the buffer.
            memcpy(buf, &mev, sizeof mev);

            // Go to next block in the buffer.
            buf = scast<char*>(buf) + sizeof(mev);
        }

        return 0;
    }
}

// Window functions for "hacky" device mouse.
namespace m {
    M m; // "Hacky" mouse.

    // Initialize and setup "hacky" mouse.
    static bool init() {
        return m.open(0);
    }

    // Deinitialize "hacky" mouse file.
    static void deinit() {
        m.close();
    }

    // Wait for mouse motion event and get it.
    deque<msys::Ev> evq; // events that has not been given to the upper layer.

    static uint waitevt(void        *buf, // Buffer to fill.
                        const size_t n)   // Number of events to get.
    {
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

        // Copy the mouse events to the buffer to be retrieved by the caller.
        for (uint i = 0; i < n; ++i) {
            // Is event queue empty?
            if (evq.empty())
                return 0; // Do not add anything new into the buffer.

            // Get mouse event from the front of the queue.
            mev = evq.front();
            memcpy(buf, &mev, sizeof mev);

            // Go to next block in the buffer.
            buf = scast<char*>(buf) + sizeof(mev);

            // Remove it from the front of the queue.
            evq.pop_front();
        }

        return 0;
    }
}

// Initialize mouse.
bool (*minit[])() {
    &evm::init, // Event mouse initialization.
    &m::init,   // "hacky" mouse initialization.
};

// Deinitialize mouse.
void (*mdeinit[])() {
    &evm::deinit, // Deinitialize event mouse device file.
    &m::deinit,   // Deinitialize mouse device file.
};

// Wait for event and get mouse motion.
static msys::Mmotion mot[] {
    &evm::waitevt, // Get event mouse motion.
    &m::waitevt    // Get "hacky" mouse motion.
};

// The deinitialize for the current mouse device that is used.
static void (*devdeinit)() = nullptr;

// Current mouse device that is used.
msys::Mmotion msys::getmot = nullptr;

// Initialize and setup mouse.
void msys::init() 
{
    using namespace msys;

    // Find and initialize an available mouse.
    for (size_t i = 0; i < sizeof(minit); ++i) {
        // Try initializing the mouse.
        if (minit[i]()) {
            // Set its function to get mouse event.
            getmot    = mot[i];
            // Set its function to clean up mouse.
            devdeinit = mdeinit[i];
            break;
        }
    }
    // Check if a mouse exists.
    if (!getmot)
        die("Failed to find a mouse on the system!");
}

// Deinitialize mouse device.
void msys::deinit() 
{
    // Is a device set to be cleaned up?
    if (devdeinit)
        devdeinit();
}
