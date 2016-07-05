#include <iostream>
#include <cstdlib>
#include "err.hpp"
using namespace std;

void die(const int code) {
    cerr << "Error code: " << hex << code << endl;
    exit(1);
}

void die(const char* msg) {
    cerr << msg;
    exit(1);
}

void error(const err& e) {
    cerr << e << endl;
}

void warn(const char *msg) {
// TODO: Yellowify!
    cout << msg;
}
