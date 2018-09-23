#include "wsys.hpp"
#include "keywait.hpp"

int main()
{
    wsys::init();
    keywait();

    wsys::movex("0", 300);
    keywait();

    return 0;
}
