#pragma once

template<class T>
class Slt {
public:
    static auto get() {
        static T s;
        return s;
    }
private:
    Slt();
};
