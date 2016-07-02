#include "types.hpp"
#include "rect.hpp"

// TODO: Make sure windows does overlap and not collide.
class Wnd {
public:
    // Create and place the window.
    Wnd(const Rect&, const Col& bg);
    // Maximize the window.
    void max();
    // Minimize the window.
    void min();
    // Draw the window.
    void draw();
private:
    // Save old position.
    void save();
    Rect cur, old;
    Col bg;
};
