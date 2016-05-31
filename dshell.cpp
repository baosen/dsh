#include <string>
using namespace std;
#include "fb.hpp"

static dshell::Fb fb;

// What about dshell?
namespace dshell {
    // Make sure windows does overlap and not collide.
    class Wnd {
    public:
    private:
    };

    // A widget is a desktop object a user can interact with.
    class Wgt : Wnd {
    protected:
        void draw();
    };

    class Pan : Wgt {
    public:
        void drag(const int x, const int y) {
        }
    };

    class Taskb {
    public:
        Taskb() {
        }
        unsigned int transparency;
    };

    class Menu : Pan {
    };

    // A dialog to ask the user questions.
    class Dlg : Wnd {
    public:
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

    class Btn : Wgt {
    public:
        Btn(const wstring label) 
            : l(label) {
            // TODO: Check if label fits the button window size.
        }

        // Change label.
        void change(const wstring label) {
            l = label;
            draw();
        }
    private:
        wstring l;
    };
}
using namespace dshell;

int main() {
    return EXIT_SUCCESS;
}
