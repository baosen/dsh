#pragma once
#include "sig.hpp"

template<T>
void erase(std::list<T>& l, T val) {
    l.erase(remove(begin(l), end(l), val), end(l));
}

template<class T>
class Slot {
public:
    virtual void recv(T& e) = 0;

    ~Slot() {
        for (auto& i : l)
            erase(l, this);
    }
private:
    std::list<Sig*> l;
    friend class Sig;
};
