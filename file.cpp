#include "file.hpp"

File::File(const char* name) : name(name), childs(nullptr), n(0) {}

File::File(const char* name, const uint n) : name(name), n(n) {
    if (n)
        childs = fnew(n);
    else // n == 0.
        childs = nullptr;
}

File::~File() {
    if (childs)
        delete[] rcast<char*>(childs);
}

File* fnew(const uint n) {
    return rcast<File*>(new char[n*sizeof(File)]);
}
