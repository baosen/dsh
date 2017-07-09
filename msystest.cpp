#include <vector>
#include <cstdio>
#include "msys.hpp"
#include "types.hpp"

// Test mouse subsystem.
int main()
{
    msys::init();

    std::vector<msys::Ev> buf(10);

    if (!msys::getmot(buf.data(), 10))
        puts("Got no data!");

    msys::deinit();
    return EXIT_SUCCESS;
}
