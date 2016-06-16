#include "keyboard.hpp"

int main()
{
    open_keyboard();

    for (;;) {
        getkbcode();
    }

    return EXIT_SUCCESS;
}
