#pragma once

class Rect {
public:
    Rect(const Pos& p, const Res& r)
        : p(p), r(r) {}

    int i() {
        return p.x+(p.y*r.w);
    }

    int size() {
        return r.h*r.w;
    }
private:
    Pos p;
    Res r;
};
