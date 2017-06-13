#include <memory>
#include <string>
#include "pos.hpp"

// Window.
class Wnd {
public:
    // Create null window.
    Wnd();
    // Create and place the window.
    Wnd(const Pos& p);

    // Drive the window and handle window events.
    void run();

    // Maximize the window.
    void max();
    // Minimize the window.
    void min();

    // Read from the picture buffer of the window.
    //virtual void read() = 0;
    // Write to the picture buffer to the window.
    //virtual void write() = 0;

    // Click on window at position p.
    virtual void click(const Pos& p) = 0;

    // Destroy the window.
    virtual ~Wnd();
protected:
    Pos cur, // Current position.
        old; // Old position.

private:
    // Save old position.
    void save();

    //std::shared_ptr<Rect> rect; // The rectangular image to draw on for the current window.

    //int                   fd;   // File descriptor.
    //std::string           name; // Name of the file for storing the rectangular image.
};
