#include <iostream>
#include <string>
#include <algorithm>
#include "gn.hpp"

void print(const std::vector<char>& v)
{
    for (const auto& c : v)
        std::cout << c;
    std::cout << std::endl;
}

std::vector<char> dup(const char *s)
{
    std::vector<char> v;

    while (*s != '\0') {
        v.push_back(*s);
        ++s;
    }
    v.push_back('\0');

    return v;
}

std::vector<char> getname(const char *in)
{
    if (in[0] != '/')
        throw 1;

    auto  d = dup(in);
    char *s = d.data();
    for (int i = d.size() - 2; i >= 0; --i) {
        if (s[i] == '/') {
            s[i] = '\0';
            continue;
        }
        break;
    }

    const char *p[2] = {0};

    while (*s) {
        if (*s == '/') {
            std::swap(p[1], p[0]);
            p[1] = s;
        }
        ++s;
    }
    p[0]++;

    std::vector<char> v(p[1] - p[0] + 1);

    int i = 0;
    while (p[1] != p[0]) {
        v[i] = *p[0];
        p[0]++;
        i++;
    }
    v[v.size()-1] = '\0';

    return v;
}
