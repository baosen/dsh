#include "kb.hpp"

int main()
{
    openkb();

    for (;;) 
        getkbcode();

    return 0;
}
