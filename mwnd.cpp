#include "mwnd.hpp"

// Construct window stored in memory.
Mwnd::Mwnd() {}
Mwnd::Mwnd(const uint size) : mem(size) {}

// Handle window click.
void Mwnd::click(const pos& p) {
}

// Access pixel.
u8& Mwnd::operator[](const uint i) {
    return mem[i];
}

// Access pixel at (x, y).
u8& Mwnd::operator()(const uint x, const uint y) {
    return mem[x + (y * mem.size())];
}
