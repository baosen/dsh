#include <iostream>
#include <vector>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/input.h>
#include "err.hpp"
#include "mouse.hpp"
using namespace std;

constexpr bool bitset(char n, ushort p) {
    return !!(n & (1u << p));
}

// Check if it is a mouse.
bool mouse(char b[EV_MAX]) {
    bool key = false, rel = false;
    for (ushort i = 0; i < EV_MAX; i++) {
        if (bitset(b[0], i)) {
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

Mouse::Mouse(In& i) {
    // Check if input device given has mouse capabilities.
}
