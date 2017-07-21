#include <iostream>
#include "gn.hpp"
using namespace std;

int main()
{
    auto v1 = getname("/asdasd/0"),
         v2 = getname("/erik/32/"),
         v3 = getname("/wnd/0/x"),
         v4 = getname("/wnd/1/y");

    print(v1);
    print(v2);
    print(v3);
    print(v4);
    return 0;
}
