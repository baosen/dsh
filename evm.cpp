#include "evm.hpp"

namespace {
    // Is bit set?
    constexpr bool bset(const char n, const ushort i) {
        return !!(n & (1 << i));
    }
    
    // Check if the file opened is a mouse.
    bool ism(char b[EV_MAX]) {
        bool key = false, rel = false;
        for (ushort i = 0; i < EV_MAX; i++) {
            // Check if bit i are set.
            if (bset(b[0], i)) {
                switch (i) {
                // Has key buttons?
                case EV_KEY:
                    key = true;
                    break;
                // Has relative axis?
                case EV_REL:
                    rel = true;
                    break;
                default:
                    break;
                }
            }
        }
        // If it has both key and relative axis, then it is mouse. If some are missing, it is not a mouse.
        return key && rel;
    }
}

// Open event mouse device file.
Evm::Evm() {}

// Find a "event" mouse and open it.
Evm::Evm(const uint i) : ev(i) {
    // Check if input device given has mouse capabilities.
    char b[EV_MAX];
    ev.evbits(b);
    if (!ism(b))
        throw err("No mouse capabilities in this event device.");
}

// Open event mouse.
bool Evm::open(const uint i) {
    return false;
}

// Read event mouse.
int Evm::rd() {
    throw err("TODO!");
}
