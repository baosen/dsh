#include "wsys.hpp"
#include "errno.hpp"
#include "wndctl.hpp"
using namespace std;

wndctl::wndctl(const std::string& pname)
    : file("ctl"), pname(pname)
{}

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
        wsys::move(pname.c_str(),       // Name of the window directory.
                   *rcast<pos*>(data)); // The position object.
        break;
    case CP:
        // TODO: Return color properties.
        break;
    default:
        break;
    }
    return SUCCESS;
}
