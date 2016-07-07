// The universal program to open, load and execute programs.
#include <iostream>
#include "path.hpp"
using namespace std;

int main() {
    const auto path = getpath();
    cout << "PATH: " << path << endl;
    const auto p = split(path);
    for (const auto& s : p)
        cout << s << endl;
    return 0;
}
