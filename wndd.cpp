#include <iostream>
#include "wndd.hpp"
#include "errno.hpp"
#include "wsys.hpp"
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
    cout << "open() called!" << endl;
    return SUCCESS;
}

// Control window.
int wndd::ioctl(int   cmd,  // The ioctl() command number passed.
                void *data) // The data.
{
    switch (cmd) {
    case wndd::MOVE:
        //wsys::move(name.c_str(), *rcast<pos*>(data));
        cout << "called!" << endl;
        break;
    default:
        break;
    }
    return SUCCESS;
}
