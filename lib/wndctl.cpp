#include "wsys.hpp"
#include "errno.hpp"
#include "wndctl.hpp"
using namespace std;

// Construct window ctl file with name as parent.
wndctl::wndctl(const std::string& pname)
    : file("ctl"), pname(pname)
{}

// Control window.
int wndctl::ioctl(const int cmd,  // The ioctl() command number passed.
                  void     *data) // The data.
{
    switch (cmd) {
    // Get color properties.
    case CP:
        *rcast<prop*>(data) = wsys::getcp(pname.c_str());
        break;
    // Move a window.
    case MOVE:
        wsys::move(pname.c_str(),       // Name of the window directory.
                   *rcast<pos*>(data)); // The position object.
        break;
    case RESIZE:
        // TODO!
        break;
    default:
        break;
    }
    return SUCCESS;
}
