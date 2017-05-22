#include "topos.hpp"

// Convert "hacky" mouse event to position.
Pos topos(const M::Ev& e) {
    return Pos(e.x, e.y);
}
