#include <iostream>
#include "dir.hpp"
#include "file.hpp"
using namespace std;

// File tree.
static dir root {
    "/", // Root directory.
    { 
        dir { 
            "kb", 
             { 
                file { "0" },
                file { "1" },
                file { "2" },
                file { "3" },
             }
        },
        dir { 
            "m", 
            { 
                file { "0" }
            }
        },
        dir {
            "wnd",
            {
                file { "0" }
            }
        }
    }
};

int main()
{
    auto e = root.getdir("/kb");
    cout << e << endl;

    e = root.getdir("/kb/");
    cout << e << endl;

    e = root.getdir("/kb/0");
    cout << e << endl;

    e = root.getdir("/kb/0/");
    cout << e << endl;

    e = root.getdir("/kb/1/");
    cout << e << endl;

    e = root.getdir("/m");
    cout << e << endl;

    e = root.getdir("/m/");
    cout << e << endl;

    e = root.getdir("/m/0");
    cout << e << endl;

    e = root.getdir("/wnd");
    cout << e << endl;

    e = root.getdir("/wnd/");
    cout << e << endl;

    return EXIT_SUCCESS;
}
