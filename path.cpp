#include <cstdlib>
#include "path.hpp"
using namespace std;

vector<string> split(const char *s) {
    vector<string> v;
    const char *cur = s;
    while (*s) {
        if (*s == ':') {
            v.push_back(string(cur, s));
            cur = ++s;
            continue;
        }
        ++s;
    }
    return v;
}

const char* getpath() {
    return getenv("PATH");
}
