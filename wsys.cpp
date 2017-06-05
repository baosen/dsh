#include <memory>
#include "wsys.hpp"
#include "wnd.hpp"
using namespace std;

namespace {
    unique_ptr<Wnd> w;
}

// Initialize and setup window system.
void wsys::init() {
    w = unique_ptr<Wnd>();
}

void wsys::write(const char* name, cohst char *buf, const off_t i, const size_t size) {
}
