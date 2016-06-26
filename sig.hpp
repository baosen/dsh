#include <list>
#include "slot.hpp"

template<class T>
class Sig {
public:
    void connect(Slot& s) {
        l.push_back(&s);
        s.l.push_back(this);
    }
    
    void disconnect(Slot& s) {
        for (const auto& i : l)
            if (&s == i)
                l.remove(i);
    }
    
    void notify(T& e) const {
        for (auto& i : l)
            s->recv(e);
    }

    ~Sig() {
    }
private:
    std::list<Slot*> l;
    friend class Slot;
};
