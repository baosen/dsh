#include <iostream>
using namespace std;

void die(const char* error) {
    cerr << error;
    exit(EXIT_FAILURE);
}

void warn(const char *msg) {
}

void error(const char *msg) {
}
