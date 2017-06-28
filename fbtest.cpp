#include "fb.hpp"

// Test framebuffer methods.
int main() 
{
    Fb fb;
    // Fill framebuffer with a color.
    for (size_t i = 0; i < fb.len(); ++i)
        fb.set(i, Col(255, 255, 255, 255));
    return 0;
}
