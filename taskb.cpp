#include <list>
#include "button.hpp"
using namespace std;

namespace {
    // Task bar.
    class Taskb {
    public:
        Taskb() {}
    private:
        list<Btn> btns;
    };

    list<Taskb> bars;
}

void make_taskb() {
    bars.push_back(Taskb());
}

void destroy_taskb() {
    bars.clear();
}
