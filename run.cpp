#include "run.hpp"

// Click on window at position p.
void Run::click(const Pos& p) {
    // Is outside window rectangle?
    if (p.x < cur.p.x || p.y < cur.p.y)
        return;
}
