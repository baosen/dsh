#include <iostream>
#include <cstdlib>
using namespace std;

void die(const char* msg) {
    cerr << msg;
    exit(1);
}

void warn(const char *msg) {
// TODO: Yellowify!
    cout << msg;
}
