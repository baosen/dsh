#include "types.hpp"
#include "pos.hpp"

class Res {
public:
    Res(const uint w, const uint h)
        : w(w), h(h) {}
private:
    const uint w, h;
};

// TODO: Make sure windows does overlap and not collide.
class Wnd {
public:
    Wnd(const Pos&, const Res&);

    // Maximize.
    void max();
    // Minimize.
    void min();
private:
    uint x, y, width, height, oldw, oldh;
};
