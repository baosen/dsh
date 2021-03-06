#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <memory>
#include <linux/input.h>
#include "fio.hpp"
#include "msys.hpp"
using namespace std;

int main()
{
    const auto fd = ::open("./sh/m/0", O_RDONLY | // Read-only.
                                       O_DIRECT); // Bypass freaking cache!
    if (fd < 0) {
        puts("Failed to open mouse file!");
        return EXIT_FAILURE;
    }

    msys::ev e;
    int      n;

    forever {
        n = ::read(fd, &e, sizeof(e));
        if (n < 0) {
            puts("Failed to read mouse file!");
            return EXIT_FAILURE;
        }
        cout << e.val << endl;
    }

    if (::close(fd) < 0) {
        puts("Failed to close mouse file!");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
