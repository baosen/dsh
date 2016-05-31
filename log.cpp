#include <iostream>
using namespace std;

namespace dshell {
    void die(const char* error) {
        cerr << error;
        exit(EXIT_FAILURE);
    }
    
    void warn(const char *msg) {
        // TODO: Yellowify!
        cout << msg;
    }
}
