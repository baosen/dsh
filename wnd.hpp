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

    // Click on window at position p.
    virtual void click(const Pos& p);
private:
    // Save old position.
    void save();

    Rect cur, // Current window.
         old; // Old window.
};
