#pragma once
#include "pos.hpp"
#include "pix.hpp"
#include "scr.hpp"
#include "dsys.hpp"

// Linux framebuffer.
class fb {
public:
    // Grab framebuffer.
    fb();
    // Release framebuffer.
    ~fb();

    // Get 8-bit color value from the framebuffer memory. Indexing in bytes.
    u8&   get8(const uint i);
    // Get 32-bit color value from the framebuffer memory. Indexing 32-bits/4 bytes at a time.
    u32&  get32(const uint i);

    // Set color value in the framebuffer.
    void  set(const uint i, const pix& c);

    // Copy provided buffer to this framebuffer.
    void  copy(const uint i, const char *buf, const size_t len);
    // Clear/blacken the entire screen.
    void  clear();

    // Get size in pixels of the framebuffer.
    size_t pixlen() const;
    // Get size in bytes of the framebuffer.
    size_t len() const;

    // Flip between buffers.
    void flip();
private:
    void setfbptrs();
    void setdbufptrs();
    void vsync();

    scr    sc;  // The screen to grab the framebuffer.

    size_t size, // Size in bytes.
           plen; // Size in pixels.

    // Bit offsets to the position of the color value.
    int roff, // Red offset.
        goff, // Green offset.
        boff, // Blue offset.
        aoff; // Alpha offset.

    bool   vsyncen; // Is vertical sync enabled.

    u8*    fbp;

    // Framebuffer methods:
    u8&  (fb::*get8p) (const uint i);
    u32& (fb::*get32p)(const uint i);
    void (fb::*flipp) ();
    void (fb::*clearp)();

    // Double buffer methods:
    u8&  dbufget8(const uint i);
    u32& dbufget32(const uint i);
    void dbufclear();
    void vsyncflip(); // Flip double buffer on vsync.

    // Double-height screen buffer methods:
    void scrflip();   // Flip "double screen" on the framebuffer device.

    // Methods for directly manipulating the framebuffer.
    u8&  fbget8(const uint i);
    u32& fbget32(const uint i);
    void nullflip();
    void fbclear();

    friend class wnd;
    friend void  dsys::init();
};
