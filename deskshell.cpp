#include <string>
using namespace std;
#include <X11/Xlib.h>
#include "log.hpp"
#include "conn.hpp"

namespace deskshell {
    class Wnd {
    };

    // A widget is a desktop object a user can interact with.
    class Widget : Wnd {
    protected:
        void draw();
    };

    class Panel : Widget {
    public:
        void drag_to(const int x, const int y) {
        }
    };

    class Taskbar {
    public:
        Taskbar() {
            c.create_window();
        }
        unsigned int transparency;
    private:
        Conn c;
    };

    class Menu : Panel {
    };

    // A dialog to ask the user questions.
    class Dlg : Wnd {
    public:
    };

    // Different ways for windows to be laid out.
    class Layout {
    protected:
        void place();
    };

    class Floating : Layout {
    };

    class Tiled : Layout {
    };
    
    enum {
        NOT_FOUND,
    };
    
    // Ask the user which file to open on the system.
    class Filedlg : Dlg {
    public:
        Filedlg(const char *pwd) {
            FILE *fp = fopen(pwd, "r");
            if (!fp)
                throw -NOT_FOUND;
        }
    private:
    };

    class Btn : Widget {
    public:
        Btn(const wstring label) : l(label) {
            // TODO: Check if label fits the button window size.
        }

        void change(const wstring label) {
            l = label;
            draw();
        }
    private:
        wstring l;
    };

}

using namespace deskshell;

int main() {
    Conn c;
    c.create_window("deskshell");
    return EXIT_SUCCESS;
}
