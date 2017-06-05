#include "run.hpp"

// Click on window at position p.
void Run::click(const Pos& p) {
    // Is outside window rectangle?
    if (p.x < cur.x || p.y < cur.y)
        return;
}

// Run program.
int main() {
    // First program ran used to load and execute other programs.
    Run r;
}
