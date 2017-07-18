#pragma once
#include <vector>
#include "wnd.hpp"

// Window stored in resizable memory.
class mwnd : public wnd {
public:
    // Construct window stored in resizable memory.
    mwnd();
    mwnd(const uint size);

    // Access pixel at index i.
    u8& operator[](const uint i);
    // Access pixel at (x, y).
    u8& operator()(const uint x, const uint y);

    // Mouse click!
    virtual void click(const pos& p);
private:
    std::vector<u8> mem;
};
