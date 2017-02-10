#include "types.hpp"
#include "rect.hpp"

// TODO: Make sure windows does overlap and not collide.
class Wnd {
public:
    // Create and place the window.
    Wnd(const Rect&);
    // Create null window.
    Wnd();
    // Maximize the window.
    void max();
    // Minimize the window.
    void min();
    // Fill entire window with colour c.
    void fill(const Col& c);
private:
    // Save old position.
    void save();
    Rect cur, old;
};
