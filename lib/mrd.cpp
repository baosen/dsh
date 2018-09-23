#include <iostream>
using namespace std;

// Return number of device files.
//static uint nfiles() 
//{
//    return 3;
//}

/*
// Discover generic "hacked" mouse.
static int discgen() 
{
    int fd, n = nfiles();
    stringstream s;
    for (int i = 0; i < n; ++i) {
        s << "/dev/input/mouse" << i;
        if ((fd = ::open(s.str().c_str(), O_RDONLY) != -1))
            return fd;
        s.str("");
    }
    throw err("No generic device found!");
}
*/

/*
// Discover mouse event file.
static int discevt() 
{
    int fd, n = nfiles();
    stringstream s;
    for (int i = 0; i < n; ++i) {
        s << "/dev/input/event" << i;
        if ((fd = ::open(s.str().c_str(), O_RDONLY) != -1))
            return fd;
        s.str("");
    }
    throw err("No event device found!");
}
*/
