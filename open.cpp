// The universal program to open, load and execute programs.
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> split(char *s) {
    vector<string> v;
    char *cur = s;
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

int main() {
    const auto path = getenv("PATH");
    cout << "PATH: " << path << endl;
    auto p = split(path);
    for (const auto& s : p)
        cout << s << endl;
    return 0;
}
