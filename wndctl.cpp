#include "wsys.hpp"
#include "errno.hpp"
#include "wndctl.hpp"
using namespace std;

// Construct window ctl file.
wndctl::wndctl(const shared_ptr<class dir>& p)
    : file("ctl"), parent(p)
{}

// Control window.
int wndctl::ioctl(int   cmd,  // The ioctl() command number passed.
                  void *data) // The data.
{
    switch (cmd) {
    case MOVE:
        wsys::move(parent->name.c_str(), *rcast<pos*>(data));
        break;
    default:
        break;
    }
    return SUCCESS;
}
