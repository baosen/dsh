#pragma once
#include <string>
#include "types.hpp"

// File parent with childs.
struct File {
    // Create file tree node.
    File(const std::string& name);

    std::string name;   // Pointer to the name of the file as a C-string.
    //File       *childs; // Children nodes.
    //uint        n;      // Number of children.
};
