#include <memory>
#include <iostream>
#include "msys.hpp"
using namespace std;

// Test mouse subsystem.
int main()
{
    msys::init();

    unique_ptr<msys::ev> e(new msys::ev);

    forever {
        uint nbytes = msys::getmot(&*e, 1);
        if (!nbytes)
            continue;
        cout << e->val << endl;
    }

    msys::deinit();
    return EXIT_SUCCESS;
}
