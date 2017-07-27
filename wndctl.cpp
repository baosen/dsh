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
int wndctl::ioctl(const int cmd,  // The ioctl() command number passed.
                  void     *data) // The data.
{
    switch (cmd) {
    // Move a window.
    case MOVE:
        wsys::move(pname.c_str(),       // Name of the window directory.
                   *rcast<pos*>(data)); // The position object.
        break;
    // Get color properties.
    case CP:
        *rcast<prop*>(data) = wsys::getcp(pname.c_str());
        break;
    default:
        break;
    }
    return SUCCESS;
}
