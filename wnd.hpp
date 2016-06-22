#include "types.hpp"

class Pos {
public:
    Pos(const unsigned int x, const unsigned int y)
        : x(x), y(y) {}
private:
    const unsigned int x, y;
};

class Res {
public:
    Res(const unsigned int w, const unsigned int h)
        : w(w), h(h) {}
private:
    const unsigned int w, h;
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
