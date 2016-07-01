#include "types.hpp"
#include "pos.hpp"
#include "res.hpp"

// TODO: Make sure windows does overlap and not collide.
class Wnd {
public:
    // Create and place the window.
    Wnd(const Rect&);
    // Maximize the window.
    void max();
    // Minimize the window.
    void min();
private:
    // Save old position.
    void save();
    Rect cur, old;
};
