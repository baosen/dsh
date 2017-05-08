#include <iostream>
#include <vector>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/input.h>
#include "evm.hpp"
#include "err.hpp"
using namespace std;

// Is bit set?
static constexpr bool bset(const char n, const ushort i) {
    return !!(n & (1 << i));
}

// Check if it is a mouse.
static bool ism(char b[EV_MAX]) {
    bool key = false, rel = false;
    for (ushort i = 0; i < EV_MAX; i++) {
        if (bset(b[0], i)) {
            switch (i) {
            case EV_KEY:
                key = true;
                break;
            case EV_REL:
                rel = true;
                break;
            default:
                break;
            }
        }
    }
    return key && rel;
}

// Open event mouse device.
Evm::Evm() : ev(0) {
}

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

int Evm::rd() {
    return 0;
}
