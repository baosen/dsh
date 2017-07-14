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
        uint nbytes = msys::getmot(&*e, 1);
        if (!nbytes)
            continue;
        cout << e->val << endl;
    }

    msys::deinit();
    return EXIT_SUCCESS;
}
