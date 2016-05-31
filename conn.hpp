#pragma once
#include <cstring>
#include <xcb/xcb_atom.h>
#include "log.hpp"

namespace dshell {
    // A X connection to a X server.
    class Conn {
    public:
        Conn();

        // Set the title of a given window.
        void set_title(const char *title) {
            xcb_change_property(c, XCB_PROP_MODE_REPLACE, w, 
                                XCB_ATOM_WM_NAME, XCB_ATOM_STRING, 
                                8, strlen(title), title);
        }

        void set_icon_name(const char* iconTitle) {
            /* Set the title of the window icon */
            xcb_change_property(c,
                                XCB_PROP_MODE_REPLACE,
                                w,
                                XCB_ATOM_WM_ICON_NAME,
                                XCB_ATOM_STRING,
                                8,
                                strlen(iconTitle),
                                iconTitle);
        }

        // Show the window on the display.
        void show() {
            /* Map the window on the screen */
            xcb_map_window(c, w);
            xcb_flush(c);
        }

        void show(const char *title) {
            make();
            set_title(title);
            show();
        }

        ~Conn() {
            xcb_disconnect(c);
        }
    private:
        // Make a window.
        void make() {
            /* Get window? */
            w = xcb_generate_id(c);
            /* Get the first screen */
            xcb_screen_t *scr = xcb_setup_roots_iterator(xcb_get_setup(c)).data;
            xcb_create_window(c, 
                              0, /* depth */
                              w,
                              scr->root, /* parent window */
                              0, 0, /* x, y */
                              250, 150, /* width, height */
                              0, /* border_width */
                              XCB_WINDOW_CLASS_INPUT_OUTPUT,
                              scr->root_visual, /* visual */
                              0, NULL); /* masks, not used */
        }

        xcb_connection_t *c;
        xcb_window_t w;
    };
}

namespace dshell {
    Conn::Conn() {
        c = xcb_connect(NULL, NULL);
        if (!c)
            die("Failed to connect to X server!");
    }
}
