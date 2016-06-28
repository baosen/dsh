#include "fb.hpp"

namespace {
    Fb fb;
}

void fill(const Rect& r, const int c) {
    fb.fill(r, c);
}
