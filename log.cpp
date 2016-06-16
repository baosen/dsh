#include <iostream>
#include <cstdlib>

void die(const char* error_message)
{
    std::cerr << error_message;
    exit(EXIT_FAILURE);
}

void warn(const char *warning_message)
{
    // TODO: Yellowify!
    std::cout << warning_message;
}
