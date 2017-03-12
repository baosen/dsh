#include "types.hpp"
#include "rect.hpp"

class Wnd {
public:
    // Create null window.
    Wnd();
    // Create and place the window.
    Wnd(const Rect&);

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
