#include <iostream>
#include <cstdlib>
#include "err.hpp"
using namespace std;

void die(const int code) {
    cerr << "\033[1;31m" << "Error code: " << hex << code << "\033[0m" << endl;
    exit(1);
}

void die(const char* e) {
    cerr << e;
    exit(1);
}

void error(const string& s) {
    cout << "\033[1;31mError:\033[0m " << s << endl;
}

void error(const err& e) {
    cout << "\033[1;31mError:\033[0m " << e << endl;
}

void warn(const char *m) {
    cout << "\033[1;33mWarning:\033[0m " << m << endl;
}
