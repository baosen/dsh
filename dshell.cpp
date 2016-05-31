#include <string>
#include <list>
using namespace std;
#include "fb.hpp"

static dshell::Fb fb;

namespace {
    // TODO: Init.
    uint newx, newy;

    uint nextx() {
        return newx;
    }

    uint nexty() {
        return newy;
    }
}

namespace dshell {
    // Make sure windows does overlap and not collide.
    class Wnd {
    public:
        Wnd(const uint x, const uint y, const uint w, const uint h) 
            : x(x), y(y), width(w), height(h) {}

        void max() {
            oldw = width;
            oldh = height;
            width = fb.maxw();
            height = fb.maxh();
            draw();
        }

        void min() {
            draw();
        }

        void draw() {}
    private:
        uint x, y, width, height, oldw, oldh;
    };

    // A widget is a desktop object a user can interact with.
    class Wgt {
    public:
        Wgt() : w(0, 0, nextx(), nexty()) {}
    private:
        Wnd w;
    };

    class Pan {
    public:
    // TODO: Drag.
    };

    // A classical button.
    class Btn : Wgt {
    public:
        Btn(const string path) {}
    private:
    };

    // Task bar.
    class Taskb {
    public:
        Taskb() {}
    private:
        list<Btn> btns;
    };

    // Different ways for windows to be laid out.
    class Lay {
    protected:
        void place();
    };

    class Float : Lay {
    };

    class Tiled : Lay {
    };
    
    enum {
        NOT_FOUND,
    };
}
using namespace dshell;

int main() {
    return EXIT_SUCCESS;
}
