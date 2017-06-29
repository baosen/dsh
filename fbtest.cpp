#include <iostream>
#include "fb.hpp"
using namespace std;

// Wait for keypress.
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

    keywait();

    // Fill framebuffer with white color.
    for (size_t i = 0; i < fb.pixlen(); ++i)
        fb.set(i, Col(255, 255, 255, 255));

    keywait();

    // Fill with red color.
    for (size_t i = 0; i < fb.pixlen(); ++i)
        fb.set(i, Col(255, 0, 0, 255));

    keywait();

    // Fill with green color.
    for (size_t i = 0; i < fb.pixlen(); ++i)
        fb.set(i, Col(0, 255, 0, 255));

    keywait();

    // Fill with blue color.
    for (size_t i = 0; i < fb.pixlen(); ++i)
        fb.set(i, Col(0, 0, 255, 255));

    keywait();

    // Fill with mixed color.
    for (size_t i = 0; i < fb.pixlen(); ++i)
        fb.set(i, Col(100, 120, 22, 255));

    keywait();

    // Fill with mixed color and no alpha.
    for (size_t i = 0; i < fb.pixlen(); ++i)
        fb.set(i, Col(10, 20, 30, 0));

    return 0;
}
