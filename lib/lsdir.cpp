#include <cstdio>
#include <cstring>
#include <vector>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include "err.hpp"
#include "dir.hpp"
using namespace std;

// List files in directory.
vector<string> lsdir(const char *name) 
{
    vector<string> dirs; // directories.
    DIR           *dir;  // directory.
    dirent        *e;    // directory entry.

    // Open directory.
    if (!(dir = opendir(name)))
        throw err("Invalid directory name.");

    // Read directory.
    if (!(e = readdir(dir)))
        throw err("Cannot read directory.");

    // List files.
    do {
        // Is entry a directory?
        if (e->d_type == DT_DIR)
            continue;
        // It is a file.
        else
            dirs.push_back(e->d_name);
    } while ((e = readdir(dir)));

    // Close directory.
    if (closedir(dir) < 0)
        throw errno;

    return dirs;
}
// based upon: http://stackoverflow.com/questions/8436841/how-to-recursively-list-directories-in-c-on-linux.
