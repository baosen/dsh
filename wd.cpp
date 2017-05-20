#include "wd.hpp"
using namespace std;

namespace dsh {
    string wd; // Current working directory for window files.
}

// Check if current working directory is set.
bool dsh::iscwdset() {
    return !wd.size();
}
