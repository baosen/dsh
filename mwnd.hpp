#pragma once
#include <vector>
#include "wnd.hpp"

// Window stored in resizable memory.
class Mwnd : public Wnd {
public:
    // Construct window stored in resizable memory.
    Mwnd();
    Mwnd(const uint size);

    // Access pixel.
    u8& operator[](const uint i);
    // Access pixel.
    u8& operator()(const uint x, const uint y);

    virtual void click(const Pos& p);
private:
    std::vector<u8> mem;
};
