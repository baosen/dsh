#include "types.hpp"
#include "wnd.hpp"

namespace {
    // TODO: Init.
    uint newx, newy;

    uint nextx() {
        return newx;
    }

    uint nexty() {
        return newy;
    }
}

// A widget is a desktop object a user can interact with.
class Wgt {
public:
    Wgt() : w(0, 0, nextx(), nexty()) {}
private:
    Wnd w;
};
