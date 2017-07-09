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
        ev.val  = e.value;
        break;
    case 1: // y-axis, - upwards, + downwards.
        ev.type = msys::Ev::Y;
        ev.val  = e.value;
        break;
    case 8: // wheel scroll, 1 up and -1 down.
        ev.type = msys::Ev::WHEEL;
        ev.val  = e.value;
        break;
    }
}

// Handle synthetic events.
static void syn(const __s32 code) // Event code reported.
{
    switch (code) {
    case SYN_REPORT:  // Done reporting an event.
        // TODO: Do something with this?
        return;
    case SYN_DROPPED: // Dropped event.
        // TODO: Throw away all frames between the reports.
        warn("SYN_DROPPED not handled.");
        return; 
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
        uint     i;

        // Put n blocks into the buffer.
        for (i = 0; i < n; ++i) {
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
                    syn(ev.code);
                    continue;
                default: {   // Log and ignore unknown events.
                    // Warn user about the unknown event.
                    stringstream ss;
                    ss << "Unknown type:" << hex << setw(2) << ev.type << endl;
                    warn(ss.str());
                    continue;
                         }
                }
                break;
            }

            // Copy mouse event block over to the buffer.
            memcpy(buf, &mev, sizeof mev);

            // Go to next block in the buffer.
            buf = scast<char*>(buf) + sizeof(mev);
        }

        return i;
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
    static void deinit() 
    {
        m.close();
    }

    static void *buf;
    static void copy(const msys::Ev& mev)
    {
        // Copy it!
        memcpy(buf, &mev, sizeof mev);
        // Go to next block in the buffer.
        buf = scast<char*>(buf) + sizeof(mev);
    }

    deque<msys::Ev> evv;

    static uint waitevt(void        *buf, // Buffer to fill.
                        const size_t n)   // Number of events to get.
    {
        // Nothing call?
        if (!n)
            return 0;

        int i  = 0;  // TODO: What to do if this becomes negative on overflow?
        m::buf = buf;

        // Leftovers?
        while (!evv.empty()) {
            copy(evv.front());
            evv.pop_front();
            i++;
            if (i >= scast<int>(n))
                return i;
        }

        while (scast<int>(n) - i > 0) {
            // Allocate mouse event.
            msys::Ev   mev;

            // Wait for input event and read it.
            const auto ev = m.rd();

#define ADD \
    if (i < n) { \
        m::copy(mev); \
        i++; \
    } else \
        m::evv.push_back(mev); \

            // Add X-axis event.
            zero(mev);
            mev.type = msys::Ev::X;
            mev.val  = ev.x;
            ADD

            // Add Y-axis event.
            zero(mev);
            mev.type = msys::Ev::Y;
            mev.val  = ev.y;
            ADD

            // Add left button event.
            zero(mev);
            mev.type = msys::Ev::LEFT;
            mev.val  = ev.left;
            ADD

            // Add middle button event.
            zero(mev);
            mev.type = msys::Ev::MID;
            mev.val  = ev.mid;
            ADD

            // Add right button event.
            zero(mev);
            mev.type = msys::Ev::RIGHT;
            mev.val  = ev.right;
            ADD
        }

        // Return the number of processed events.
        return i;
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
