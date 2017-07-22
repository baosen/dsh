#include "wndd.hpp"
#include "errno.hpp"
using namespace std;

// Create window directory and insert files.
// name:  name of the directory.
// files: files to insert.
wndd::wndd(const string& name, const entlist& files)
    : dir(name, files)
{}

// Open window directory.
int wndd::open(const char *path)
{
    return SUCCESS;
}

// Control window.
int wndd::ioctl(int   cmd, // The ioctl() command number passed.
                void *arg) // The arguments provided to the ioctl() call.
{
    switch (cmd) {
    case wndd::MOVE:
        break;
    default:
        break;
    }
    return SUCCESS;
}
