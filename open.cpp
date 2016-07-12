// The universal program to open, load and execute programs.
#include <iostream>
#include <cstdio>
#include "path.hpp"
using namespace std;

auto open(const vector<string>& paths) {
    vector<FILE*> v;
    for (const auto& p : paths) {
        const auto f = fopen(p.c_str(), "r");
        if (!f)
            continue;
        v.push_back(f);
    }
    return v;
}

int main() {
    const auto path = getpath();
    cout << "PATH: " << path << endl;
    const auto p = split(path);
    for (const auto& s : p)
        cout << s << endl;
    return 0;
}
