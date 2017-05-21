#include <memory>
#include "wsys.hpp"
#include "wnd.hpp"
using namespace std;

namespace {
    unique_ptr<Wnd> w;
}

// Initialize and setup window system.
void initw() {
    w = unique_ptr<Wnd>();
}
