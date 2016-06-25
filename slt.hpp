#pragma once

template<class T>
class Slt<T> {
public:
    static Slt<T>& get() {
        static T s;
        return s;
    }
private:
    Slt();
};
