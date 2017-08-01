#include <vector>
#include "scr.hpp"
#include "types.hpp"

// Background image.
class bg : public std::vector<u32> {
public:
    void update();
private:
    std::vector<u32> vec;
};
