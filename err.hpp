#include <stdexcept>
using err = std::runtime_error;

inline ostream& operator<<(ostream& o, const err& e) {
    o << e.what();
    return o;
}

enum class Err {
    FAILED,
};
