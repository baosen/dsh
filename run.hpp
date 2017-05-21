#pragma once
#include "wnd.hpp"

// Run a program.
class Run : public Wnd {
public:
    // Click on window at position p.
    virtual void click(const Pos& p);
private:
};
