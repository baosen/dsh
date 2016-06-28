#include "types.hpp"
#include "pos.hpp"
#include "res.hpp"

// TODO: Make sure windows does overlap and not collide.
class Wnd {
public:
    Wnd(const Pos&, const Res&);

    // Maximize.
    void max();
    // Minimize.
    void min();
private:
    void save();

    uint x, y, width, height, oldw, oldh;
};
