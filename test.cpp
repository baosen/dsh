#include "slt.hpp"
#include "kb.hpp"

int main()
{
    auto kb = Slt<Kb>::get();

    for (;;)
        kb.getkbcode();

    return 0;
}
