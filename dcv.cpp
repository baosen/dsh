#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/input.h>
#include "err.hpp"
#include "dcv.hpp"
using namespace std;

static constexpr bool bitset(char n, ushort p) {
    return !!(n & (1u << p));
}

// Check if it is a mouse.
static bool ism(char b[EV_MAX]) {
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

// Discover mice connected to the system.
vector<Mouse> mdcv() {
    vector<Mouse> m;
    // Iterate through devices.
    DIR           *dir; // directory.
    struct dirent *e;   // directory entry.
    // Open directory.
    if (!(dir = opendir("/dev/input/")))
        throw err("Cannot open /dev/input/!");
    // Read directory.
    if (!(e = readdir(dir)))
        throw err("Cannot read input directory.");
    do {
        // Is entry a directory?
        if (e->d_type == DT_DIR)
            continue;
        // It is a file.
        else {
            // Check if it is a mouse.
            In i(e->d_name);
            char b[EV_MAX];
            i.evbits(b);
            if (ism(b))
                m.push_back(Mouse(i));
            else
                continue;
        }
    } while ((e = readdir(dir)));
    if (closedir(dir) < 0)
        throw errno;
    return m;
}
