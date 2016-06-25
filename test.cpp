#include "slt.hpp"
#include "kb.hpp"
#include "types.hpp"

int main()
{
    auto kb = Slt<Kb>::get();
    forever {
        kb.getkbcode();
    }
    return 0;
}
