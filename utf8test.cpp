#include "utf8.hpp"

int main()
{
    UTF8char c1(u8"a"),          // n = 1.
             c2(u8"å"),          // n = 2.
             c3(u8" "),          // n = 1.
             c4(u8"\U0010FFFF"); // n = 4.
    return 0;
}
