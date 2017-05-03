#include "types.hpp"
#include "rect.hpp"

class Wnd {
public:
    // Protocol opcodes.
    enum class Op : s8 {
        max,   // User wants to maximize window.
        min,   // User wants to minimize window.
        click, // User clicks somewhere on the window.
        fill,  // User wants to fill window with a color.
        text,  // User wants to texture a window. Sends a raw or compressed texture. User chooses driver.
    };
    
    // Create null window.
    Wnd();
    // Create and place the window.
    Wnd(const Rect&);

    // Maximize the window.
    void max();
    // Minimize the window.
    void min();

    // Click on window at position p.
    virtual void click(const Pos& p);

    // Fill entire window with colour c.
    void fill(const Col& c);
private:
    // Save old position.
    void save();

    Rect cur, // Current window.
         old; // Old window.
};
