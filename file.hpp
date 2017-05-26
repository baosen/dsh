#pragma once
#include "types.hpp"

// File parent with childs.
struct File {
    // Create file tree node.
    File(const char* name);

    // Create file tree node with n childs.
    File(const char* name, const uint n);

    // Destroy file and its childs.
    ~File();

    const char *name;   // Pointer to the name of the file as a C-string.
    File       *childs; // Children nodes.
    uint        n;      // Number of children.
};

File* fnew(const uint n);
