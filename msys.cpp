// Mouse subsystem.
#include "msys.hpp"
#include "evm.hpp"
#include "m.hpp"
#include "log.hpp"

// Window functions for event device mouse.
namespace evm {
    Evm e; // Event mouse device.

    // Open mouse event device.
    static bool init() {
    }

    // Returns mouse position as two unsigned integers from the event mouse file.
    static void pos(void *buf) {
        const auto ev = e.rd();
    }
}

// Window functions for "hacky" device mouse.
namespace m {
    M m; // "Hacky" mouse.

    static bool init() {
        return m.open(0);
    }

    // Returns mouse positon as uints from "hacky" mouse.
    static void pos(void *buf) {
        throw err("TODO!");
    }
}

// Initialize mouse.
bool (*minit[])() {
    &evm::init, // Event mouse initialization.
    &m::init,   // "hacky" mouse initialization.
};

// Get mouse position.
static msys::Mposf mpos[] {
    &evm::pos, // Get event mouse position.
    &m::pos    // Get "hacky" mouse position.
};

// Current mouse device that is used.
msys::Mposf msys::pos = nullptr;

// Initialize and setup mouse.
void msys::init() {
    using namespace msys;

    // Find and initialize an available mouse.
    for (uint i = 0; i < sizeof(minit); ++i) {
        // Try initializing the mouse.
        if (minit[i]()) {
            // Set its function to get the position of the mouse.
            msys::pos = mpos[i];
            break;
        }
    }
    if (!msys::pos)
        die("Failed to find a mouse on the system!");
}
