// The universal program to open, load and execute programs.
#include <cstdlib>
#include <iostream>
using namespace std;

int main() {
    const auto path = getenv("PATH");
    cout << "PATH: " << path << endl;
    return 0;
}
