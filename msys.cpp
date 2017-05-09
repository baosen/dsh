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
        return e.open(0);
    }

    // Returns mouse position from event mouse.
    static Pos pos() {
        return Pos(0, 0);
    }
}

// Window functions for "hacky" device mouse.
namespace m {
    M m; // "Hacky" mouse.

    static bool init() {
        return m.open(0);
    }

    // Returns user movement.
    static Pos pos() {
        return Pos(0, 0);
    }
}

// Init mouse.
bool (*minit[])() = {
    &evm::init, &m::init,
};

// Get mouse position.
static MPosFunc mpos[] = {
    &evm::pos, &m::pos
};

// Current mouse device that is used.
MPosFunc mcurpos = nullptr;

// Initialize and setup mouse.
void initm() {
    // Find and initialize an available mouse.
    for (int i = 0; i < sizeof(minit); ++i) {
        if (minit[i]()) {
            mcurpos = mpos[i];
            break;
        }
    }
    if (!mcurpos) {
        error("Failed to find mouse on the computer system!");
        exit(EXIT_FAILURE);
    }
}
