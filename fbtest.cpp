#include <iostream>
#include "fb.hpp"
using namespace std;

static void keywait() 
{
    cout << "Press any key." << endl;
    cin.get();
}

// Test framebuffer methods.
int main() 
{
    // Open framebuffer file.
    Fb fb;

    // Fill framebuffer with white color.
    for (size_t i = 0; i < fb.pixlen(); ++i)
        fb.set(i, Col(255, 255, 255, 0));

    keywait();

    // Fill with red color.
    for (size_t i = 0; i < fb.pixlen(); ++i)
        fb.set(i, Col(255, 0, 0, 0));

    keywait();

    // Fill with green color.
    for (size_t i = 0; i < fb.pixlen(); ++i)
        fb.set(i, Col(0, 255, 0, 0));

    keywait();

    // Fill with blue color.
    for (size_t i = 0; i < fb.pixlen(); ++i)
        fb.set(i, Col(0, 0, 255, 0));

    keywait();

    // BUG: Using alpha breaks the color.

    return 0;
}
