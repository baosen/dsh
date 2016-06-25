#include "fbslt.hpp"
#include "slt.hpp"

Fb& getfb() {
    return Slt<Fb>::get();
}
