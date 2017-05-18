#include "frect.hpp"

class Wnd {
public:
    // Protocol opcodes.
    enum class Op : s8 {
        max,   // User wants to maximize window.
        min,   // User wants to minimize window.
        click, // User clicks somewhere on the window.
        copy,  // User wants to copy an existing rectangular image to a window. Sends a raw or compressed rectangular image. User chooses driver.
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
private:
    // Save old position.
    void save();

    Frect cur, // The image to draw on for the current window.
          old; // Saved image of an old window.
};
