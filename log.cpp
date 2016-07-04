#include <iostream>
#include <cstdlib>
using namespace std;

void die(const int code) {
    cerr << "Error code: " << hex << code << endl;
    exit(1);
}

void die(const char* msg) {
    cerr << msg;
    exit(1);
}

void warn(const char *msg) {
// TODO: Yellowify!
    cout << msg;
}
