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
bool mouse(char b[EV_MAX]) {
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

Mouse::Mouse(In& i) {
    // Check if input device given has mouse capabilities.
}

// Read mouse input.
deque<Mouse::Evt> Mouse::rd() {
}
