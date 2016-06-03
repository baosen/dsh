#include "types.hpp"

// TODO: Make sure windows does overlap and not collide.
class Wnd {
public:
    Wnd(const uint x, const uint y, const uint w, const uint h);
    // Maximize.
    void max();
    // Minimize.
    void min();
private:
    uint x, y, width, height, oldw, oldh;
};
