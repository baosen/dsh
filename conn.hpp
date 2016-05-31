#include <cstring>
#include <xcb/xcb.h>
#include <xcb/xcb_atom.h>

namespace deskshell {
    class Conn {
    public:
        Conn() {
            c = xcb_connect(NULL, NULL);
            if (!c);
                //die("Failed to connect to X server!");
        }

        void create_window() {
            /* Get window? */
            w = xcb_generate_id(c);
            /* Get the first screen */
            xcb_screen_t *scr = xcb_setup_roots_iterator(xcb_get_setup(c)).data;
            xcb_create_window(c, 
                              0,                             /* depth */
                              w,
                              scr->root,                  /* parent window */
                              0, 0,                          /* x, y */
                              250, 150,                      /* width, height */
                              10,                            /* border_width */
                              XCB_WINDOW_CLASS_INPUT_OUTPUT, /* class */
                              scr->root_visual,           /* visual */
                              0, NULL);                      /* masks, not used */
        }

        void create_window(const char *title) {
            create_window();
            /* Set the title of the window */
            xcb_change_property(c,
                                XCB_PROP_MODE_REPLACE,
                                w,
                                XCB_ATOM_WM_NAME,
                                XCB_ATOM_STRING,
                                8,
                                strlen(title),
                                title);
            ///* Set the title of the window icon */
            //const char *iconTitle = "Hello World ! (iconified)";
            //xcb_change_property(c,
            //                    XCB_PROP_MODE_REPLACE,
            //                    w,
            //                    XCB_ATOM_WM_ICON_NAME,
            //                    XCB_ATOM_STRING,
            //                    8,
            //                    strlen(iconTitle),
            //                    iconTitle);
            /* Map the window on the screen */
            xcb_map_window(c, w);
            xcb_flush(c);
        }

        void listen() {
        }

        ~Conn() {
            xcb_disconnect(c);
        }
    private:
        xcb_connection_t *c;
        xcb_window_t w;
    };
}
