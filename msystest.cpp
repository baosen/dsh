#include <vector>
#include <cstdio>
#include <iostream>
#include "msys.hpp"
#include "types.hpp"
using namespace std;

// Test mouse subsystem.
int main()
{
    msys::init();

    std::vector<msys::Ev> buf(10);

    uint n;
    if (!(n = msys::getmot(buf.data(), 1))) {
        puts("Got no data!");
        return EXIT_FAILURE;
    }
    cout << "Got " << n << " events!" << endl;

    msys::deinit();
    return EXIT_SUCCESS;
}
