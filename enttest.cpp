#include <iostream>
#include <cassert>
#include "dir.hpp"
#include "file.hpp"
using namespace std;

typedef initializer_list<shared_ptr<ent>> ptrlist;

// File tree.
static dir root { // TODO: Remove root directory, which I think is unnecessary.
    "/",          // Root directory.
    { 
        make_shared<dir>
        (    
            "kb", 
            ptrlist
            { 
                shared_ptr<ent>(new file("0"))
            }
        ),
        make_shared<dir>
        (   
            "m", 
            ptrlist
            { 
                shared_ptr<ent>(new file("0"))
            }
        ),
        make_shared<dir>
        (   
            "wnd", 
            ptrlist
            { 
                shared_ptr<ent>(new file("0"))
            }
        )
    }
};

void print(const shared_ptr<ent>& e)
{
    if (*e) {
        cout << e << endl;
        return;
    }
    cout << "None" << endl;
}

int main()
{
    auto e = root.getdir("/kb");
    print(e);
    assert(*e);

    e = root.getdir("/kb/");
    print(e);
    assert(*e);

    e = root.getdir("/kb/0");
    print(e);
    assert(!*e);

    e = root.getdir("/kb/0/");
    print(e);
    assert(!*e);

    e = root.getdir("/kb/1");
    print(e);
    assert(!*e);

    e = root.getdir("/kb/1/");
    print(e);
    assert(!*e);

    e = root.getdir("/m");
    print(e);
    assert(*e);

    e = root.getdir("/m/");
    print(e);
    assert(*e);

    e = root.getdir("/m/0");
    print(e);
    assert(!*e);

    e = root.getdir("/wnd");
    print(e);
    assert(*e);

    e = root.getdir("/wnd/");
    print(e);
    assert(*e);

    e = root.getdir("/wnd/0");
    print(e);
    assert(!*e);

    e = root.getdir("/wnd/1");
    print(e);
    assert(!*e);

    e = root.getfile("/wnd/0");
    print(e);
    assert(*e);

    e = root.getfile("/wnd/0/");
    print(e);
    assert(*e);

    e = root.getfile("/wnd/1/");
    print(e);
    assert(!*e);

    return EXIT_SUCCESS;
}
