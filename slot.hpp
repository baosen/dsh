#pragma once
#include "sig.hpp"

template<class T>
class Slot {
public:
    virtual void recv(T& e) = 0;
    ~Slot() {
        for (auto& i : l)
            if (i->l.contains(this))
                i->l.remove(this);
    }
private:
    std::list<Sig*> l;
    friend class Sig;
};
