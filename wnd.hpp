#pragma once
#include "pos.hpp"
#include "rect.hpp"

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
    void read(char *buf, off_t offset, size_t size) noexcept;
    // Write to the picture buffer to the window. Returns exactly the number of bytes written except on error.
    void write(const char *buf, off_t offset, size_t size) noexcept;

    // Click on window at position p.
    virtual void click(const Pos& p) = 0;

    // Destroy the window.
    virtual ~Wnd();
protected:
    Pos pcur, // Current position.
        pold; // Old position.

private:
    // Save old position.
    void save();

    Rect rcur, // The current rectangular image to draw on for the current window.
         rold; // The old rectangular image to draw on for the current window.
};
