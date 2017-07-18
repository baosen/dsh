#include "topos.hpp"

// Convert "hacky" mouse event to position.
pos topos(const m::ev& e) 
{
    return pos(e.x, e.y);
}
