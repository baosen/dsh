#include "keywait.hpp"
#include "rect.hpp"

int main()
{
    Rect r1(Pos(400, 400), Res(100, 100)),
         r2(Pos(200, 200), Res(100, 100));

    r1.fill(Pix(255, 255, 255, 255));
    keywait();
    r2.fill(Pix(255, 0, 255, 255));
    keywait();

    return EXIT_SUCCESS;
}
