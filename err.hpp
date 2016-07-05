#pragma once
#include <iostream>
#include <stdexcept>
using err = std::runtime_error;

inline std::ostream& operator<<(std::ostream& o, const err& e) {
    o << e.what();
    return o;
}

enum class Err {
    FAILED,
};
