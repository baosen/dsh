#include <iostream>
#include "ent.hpp"
using namespace std;

// File tree.
static ent root {
    "/",            // Root directory.
    S_IFDIR | 0755, // Is a directory ORed with the permission bits.
    { 
        { 
            "kb", 
             S_IFDIR | 0755,
             { 
                { "0", S_IFREG | 0444 },
                { "1", S_IFREG | 0444 },
                { "2", S_IFREG | 0444 },
                { "3", S_IFREG | 0444 },
             }
        },
        { 
            "m", 
            S_IFDIR | 0755,
            { 
                { "0", S_IFREG | 0444 }
            }
        },
        {
            "wnd",
            S_IFDIR | 0755,
            {
                { "0", S_IFREG | 0444 }
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
