#include <iostream>
#include <vector>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/input.h>
#include "err.hpp"
#include "mouse.hpp"
using namespace std;

// Is bit set?
constexpr bool bset(const char n, const ushort i) {
    return !!(n & (1u << i));
}

// Check if it is a mouse.
static bool mouse(char b[EV_MAX]) {
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

// Find a mouse and open it.
Evm::Evm(Evt& e) : oldl(false), oldr(false), oldm(false) {
    // Check if input device given has mouse capabilities.
    char b[EV_MAX];
    e.evbits(b);
    if (!mouse(b))
        throw err("No mouse capabilities in this event device.");
}
