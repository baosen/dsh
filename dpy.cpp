#include <sstream>
#include "err.hpp"
#include "log.hpp"
#include "fio.hpp"
#include "dpy.hpp"
using namespace std;

// Open a display directory specified by the given path.
dpy::dpy(const string& path) 
{
    // Create display directory containing all window and rectangle files.
    static uint i = 0;
    // TODO: Parse and traverse path.
    stringstream ss;
    ss << path << "dpy" << i << '/';
    // TODO: Create file from FUSE driver.
    dirpath = ss.str();
    ++i;
}

// Disconnect from the display.
dpy::~dpy() 
{
    die("TODO: Implement closing display.");
}
