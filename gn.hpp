#pragma once
#include <vector>

// Print the characters in the vector to standard output.
void              print(const std::vector<char>& v);

// Copy the characters into a new vector.
std::vector<char> dup(const char *s);

// Get the name of a file in a path string.
std::vector<char> getname(const char *in);
