#pragma once
#include "wnd.hpp"

// Do an action.
class Do : public Wnd {
public:
    // Click on window at position p.
    virtual void click(const Pos& p);
private:
};
