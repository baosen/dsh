#include <list>
#include <unordered_map>
#include <string>
#include "wsys.hpp"
#include "mwnd.hpp"
using namespace std;

namespace {
    unordered_map<string, Mwnd> wnds;
}

// Initialize and setup window system.
void wsys::init() {
    // Add a single window.
    wnds["dpy0"] = Mwnd();
}

// Read from window.
void wsys::read(const char* name, const char *buf, const off_t i, const size_t size) {
}

// Write from window.
void wsys::write(const char* name, const char *buf, const off_t i, const size_t size) {
}
