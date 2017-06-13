#include "err.hpp"
using namespace std;

// Print error code and exit.
void die(const int code) {
    cerr << "\033[1;31m" << "Error code: " << hex << code << "\033[0m" << endl;
    exit(code);
}

// Print error and exit.
void die(const char* e) {
    cerr << e;
    exit(errno);
}

// Print error.
void error(const string& s) {
    cout << "\033[1;31mError:\033[0m " << s << endl;
}

// Print error.
void error(const err& e) {
    cout << "\033[1;31mError:\033[0m " << e << endl;
}

// Print warning.
void warn(const char *m) {
    cout << "\033[1;33mWarning:\033[0m " << m << endl;
}
