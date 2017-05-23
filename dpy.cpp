#include <boost/filesystem.hpp>
#include <sstream>
#include "err.hpp"
#include "log.hpp"
#include "fio.hpp"
#include "dpy.hpp"
using namespace std;
using namespace boost::filesystem;

// Open a display directory specified by the given path.
Dpy::Dpy(const string& path) {
    // Create display directory containing all window and rectangle files.
    static uint i = 0;
    // TODO: Parse and traverse path.
    stringstream ss;
    ss << path << "dpy" << i << '/';
    create_directory(ss.str());
    dirpath = ss.str();
    ++i;
}

// Disconnect from the display.
Dpy::~Dpy() {
    // Delete all files in the display directory.
    try {
        //remove_all(dirpath);
    } catch (...) {
        die("Display exception.");
    }
}
