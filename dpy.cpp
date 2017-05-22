#include <boost/filesystem.hpp>
#include "err.hpp"
#include "log.hpp"
#include "fio.hpp"
#include "dpy.hpp"
using namespace std;
using namespace boost::filesystem;

// Open a display directory specified by the given path.
Dpy::Dpy(const string& path) {
    create_directory(path);
    dirpath = path;
}

// Disconnect from the display.
Dpy::~Dpy() {
    remove_all(dirpath);
}
