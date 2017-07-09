#include <memory>
#include <iostream>
#include "msys.hpp"
using namespace std;

// Test mouse subsystem.
int main()
{
    msys::init();

    unique_ptr<msys::Ev> e(new msys::Ev);

    forever {
        uint n = msys::getmot(&*e, 1);
        if (!n)
            continue;
        cout << e->val << endl;
    }

    msys::deinit();
    return EXIT_SUCCESS;
}
