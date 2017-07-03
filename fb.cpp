#include <cstring>
#include <sys/mman.h>
#include "fb.hpp"
#include "log.hpp"
using namespace std;

// Setup framebuffer file mapping to the address space.
Fb::Fb() 
    : roff(-1), goff(-1), boff(-1), aoff(-1), // Blanken color offsets.
      vsyncen(true)                           // Enable vertical sync.
{
    // Check if double buffer using double height of virtual screen is setup.
    if (scr.dbufen) {
        // Get size of framebuffer in bytes and half it to accommedate for the virtual screen.
        size = scr.finfo().smem_len / 2;
        // Do not use any allocated double buffer in the system memory.
        dbuf = nullptr;
    } else { // No double buffer setup for the framebuffer screen.
        // Get size of framebuffer in bytes.
        size = scr.finfo().smem_len;
        // Set function pointers for manipulating the framebuffer.
        setptrs();
    }

    // Compute number of pixels.
    plen = size / sizeof(u32);

    // Map framebuffer to computer's address space.
    fb = scast<u8*>(mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, scr.fd, 0));

    // Set the positions to the color bits.
    const auto v = scr.vinfo();
    if (v.red.length)
        roff = v.red.offset;    // Position to red bits.
    if (v.green.length)
        goff = v.green.offset;  // Position to green bits.
    if (v.blue.length)
        boff = v.blue.offset;   // Position to blue bits.
    if (v.transp.length)
        aoff = v.transp.offset; // Position to alpha-transparency bits.
}

void Fb::setptrs()
{
    // Try waiting for vertical sync to check if it is available.
    vsyncen = scr.isvsync();
    if (vsyncen) {
        // Set size of the double buffer to be the same as the framebuffer size in bytes.
        dbuf = make_unique<u8[]>(size);
        // Set function pointers to use the double buffer functions.
        setdbufptrs();
    } else
        // Set function pointers to use the direct framebuffer manipulation functions.
        setfbptrs();
}

void Fb::setfbptrs()
{
    get8p  = &Fb::fbget8;
    get32p = &Fb::fbget32;
    flipp  = &Fb::nullflip;
    clearp = &Fb::fbclear;
}

void Fb::setdbufptrs()
{
    get8p  = &Fb::dbufget8;
    get32p = &Fb::dbufget32;
    flipp  = &Fb::dbufflip;
    clearp = &Fb::dbufclear;
}

// Unmap framebuffer from the system address space.
Fb::~Fb() 
{
    // Unmap framebuffer.
    if (munmap(fb, size) < 0)
        die("Failed to unmap the framebuffer from the system's address space!");
}

// Set color value in the framebuffer.
void Fb::set(const uint i, // Index to set the color value to.
             const Pix& c) // Color to set.
{
    get32(i) = c.val(roff, goff, boff, aoff);
}

// Get size in bytes of the framebuffer.
size_t Fb::len() const 
{
    return size;
}

// Get size in pixels of the framebuffer.
size_t Fb::pixlen() const
{
    return plen;
}

//
// TODO: Set a function pointer rather than check using an if boolean check.
//

#define CALLMEMBFN(p) (this->*(p))

// Access framebuffer memory 8 bits at a time.
u8& Fb::get8(const uint i) // Index beginning at 0 indexing a string of framebuffer bytes.
{
    return CALLMEMBFN(get8p)(i);
}

u8& Fb::dbufget8(const uint i) // Index beginning at 0 indexing a string of framebuffer bytes.
{
    return dbuf[i];
}

u8& Fb::fbget8(const uint i) // Index beginning at 0 indexing a string of framebuffer bytes.
{
    return fb[i];
}

// Access framebuffer memory 32 bits at a time.
u32& Fb::get32(const uint i) // Index beginning at 0 indexing a string of framebuffer bytes. 
{
    return CALLMEMBFN(get32p)(i);
}

u32& Fb::dbufget32(const uint i) // Index beginning at 0 indexing a string of framebuffer bytes. 
{
    return *(rcast<u32*>(&dbuf[0]) + i);
}

u32& Fb::fbget32(const uint i) // Index beginning at 0 indexing a string of framebuffer bytes. 
{
    return *(rcast<u32*>(&fb[0]) + i);
}

// Copy provided buffer to this framebuffer.
void Fb::copy(const uint   i,   // Index indexing into the buffer array of bytes.
              const char  *buf, // Pointer to the buffer array itself.
              const size_t len) // Length/size of the buffer in bytes.
{
    memcpy(&dbuf[i], buf, len);
}

// Wait for vertical sync.
void Fb::vsync()
{
    // Try waiting for vertical sync.
    try {
        scr.vsync();
    } catch (const err& e) {
        // Disable vertical sync, because it is not supported.
        vsyncen = false;
        throw;
    }
}

// Flip between two buffers, thus reduce tearing.
void Fb::flip()
{
    CALLMEMBFN(flipp)();
}

// Double buffer flip.
void Fb::dbufflip()
{
    // Blit by copying the double buffer into the framebuffer.
    if (scr.dbufen) {
        scr.flip();
        // TODO: Change pointer.
        return;
    }

    // Wait for vertical sync before copying.
    this->vsync();
    // Copy double buffer into the framebuffer.
    memcpy(fb, &dbuf[0], size);
}

// Do no flip if manipulating directly to framebuffer.
void Fb::nullflip() {}

// Clear/blacken the entire screen.
void Fb::clear()
{
    CALLMEMBFN(clearp)();
}

// Double-buffered clear.
void Fb::dbufclear()
{
    memset(&dbuf[0], 0, size);
}

// Clear framebuffer directly.
void Fb::fbclear()
{
    memset(&fb[0], 0, size);
}
