#include "mwnd.hpp"

// Construct window stored in memory.
mwnd::mwnd() {}
// Construct window stored in memory of size.
mwnd::mwnd(const uint size) : mem(size) {}

// Handle window click.
void mwnd::click(const pos& p) 
{
}

// Access pixel.
u8& mwnd::operator[](const uint i) 
{
    return mem[i];
}

// Access pixel at (x, y).
u8& mwnd::operator()(const uint x, const uint y) 
{
    return mem[x + (y * mem.size())];
}
