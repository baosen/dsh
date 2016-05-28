#include <string>
using namespace std;
#include <X11/Xlib.h>
#include "log.hpp"

namespace deskshell {
    // A widget is a desktop object a user can interact with.
    class Widget {
    protected:
        void draw();
    };

    class Panel {
    };

    class Task_bar : Panel {
    };

    class Panel_widget : Widget {
    };

    class Menu : Panel_widget {
    };

    class Window {
    };

    // A dialog to ask the user questions.
    class Dialog : Window {
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
    class File_dialog : Dialog {
    public:
        File_dialog(const char *pwd) {
            FILE *fp = fopen(pwd, "r");
            if (!fp)
                throw -NOT_FOUND;
        }
    private:
    };

    class Button : Widget {
    public:
        Button(const wstring label) 
            : label(label) {}

        void change_label(const wstring new_label) {
            label = new_label;
            draw();
        }
    private:
        wstring label;
    };
}

int main() {
    auto display = XOpenDisplay(NULL);
    if (!display)
        deskshell::die("Failed to open main display!");
    return EXIT_SUCCESS;
}
