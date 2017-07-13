#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <linux/input.h>
#include "fio.hpp"
#include "locale.hpp"
#include "kbc.hpp"
using namespace std;

// TODO: Test with no O_DIRECT.

int main()
{
    const auto fd = ::open("./sh/kb0", O_RDONLY | // Read-only.
                                       O_DIRECT); // Bypass freaking cache!
    if (fd < 0) {
        puts("Failed to open keyboard file!");
        return EXIT_FAILURE;
    }

    // Set locale to output wide characters in console.
    setwc();

    wchar_t     c;
    input_event e;
    int         n;
    for (;;) {
        n = ::read(fd, &e, sizeof(e));
        if (n < 0) {
            puts("Failed to read keyboard file!");
            return EXIT_FAILURE;
        }
        c = towc(e);
        if (c == '\0') {
            //wcout << L"code: " << hex << e.code << dec << endl;
            //goto exit;
            continue;
        }
        wcout << L"code: " << hex << e.code << dec << L'\n'
              << L"char: " << c << endl;
        //goto exit;
    }

exit:
    if (::close(fd) < 0) {
        puts("Failed to close keyboard file!");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
