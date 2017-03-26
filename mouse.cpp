#include <linux/input.h>
#include <iostream>
#include "mouse.hpp"
using namespace std;

constexpr bool 
bitset(char n, ushort p) {
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

Mouse::Mouse() {
    // Iterate through devices.
    In i("/dev/input/event0");

    // Check if it is a mouse.
    char b[EV_MAX];
    i.evbits(b);
    if (mouse(b))
        cout << "yes!" << endl;
    else
        cout << "no..." << endl;
    // Find a device that has mouse capabilities.
}
