#include <cwchar>
#include <iostream>
#include "locale.hpp"

// Set locale to ALL to enable printing out in wide characters.
// BEWARE: calling any ASCII print functions like printf sets its back!
void setwc()
{
    setlocale(LC_ALL, "");
/*
    if (fwide(stdout, 1) <= 0) {
        puts("Could not switch to wide character mode!");
        exit(EXIT_FAILURE);
    }
*/
}
