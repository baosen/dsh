#include <memory>
#include <string>
#include "frect.hpp"
#include "pos.hpp"

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
    Wnd(const Pos& p);

    // Maximize the window.
    void max();
    // Minimize the window.
    void min();

    // Click on window at position p.
    virtual void click(const Pos& p) = 0;

    // Destroy the window.
    ~Wnd();

protected:
    std::shared_ptr<Rect> cur; // The image to draw on for the current window.

private:
    // Save old position.
    void save();

    std::shared_ptr<Rect> old; // Saved image of an old window.

    int fd;           // File descriptor.
    std::string name; // Name of the file for storing the rectangular image.
};
