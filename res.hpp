#pragma once

class Rect;

class Res {
public:
    Res(const uint w, const uint h)
        : w(w), h(h) {}
private:
    const uint w, h;

    friend class Rect;
};
