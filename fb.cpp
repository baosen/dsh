#include <cstring>
#include <sys/mman.h>
#include "fb.hpp"
#include "log.hpp"
using namespace std;

// Setup framebuffer file mapping to the address space.
fb::fb() 
    : roff(-1), goff(-1), boff(-1), aoff(-1), // Blanken color offsets.
      vsyncen(true)                           // Enable vertical sync.
{
    // Check if double buffer using double height of virtual screen is setup.
    if (sc.dbufen) {
        // Get size of framebuffer in bytes and half it to accommedate for the virtual screen.
        size = sc.finfo().smem_len / 2;
        // Do not use any allocated double buffer in the system memory.
        dbuf = nullptr;
    } else // No double buffer setup for the framebuffer screen.
        // Get size of framebuffer in bytes.
        size = sc.finfo().smem_len;

    // Set function pointers for manipulating the framebuffer.
    setptrs();

    // Compute number of pixels.
    plen = size / sizeof(u32);

    // Map framebuffer to computer's address space.
    fbp = scast<u8*>(mmap(nullptr, size, 
                          PROT_READ | PROT_WRITE, // Read and write access!
                          MAP_SHARED, sc.fd, 0));

    // Set the positions to the color bits.
    const auto v = sc.vinfo();
    if (v.red.length)
        roff = v.red.offset;    // Position to red bits.
    if (v.green.length)
        goff = v.green.offset;  // Position to green bits.
    if (v.blue.length)
        boff = v.blue.offset;   // Position to blue bits.
    if (v.transp.length)
        aoff = v.transp.offset; // Position to alpha-transparency bits.
}

// Set the function pointers to manipulate the framebuffer according to the supported control calls.
void fb::setptrs()
{
    // Try waiting for vertical sync to check if it is available.
    vsyncen = sc.isvsync();
    if (vsyncen) {
        // Set size of the double buffer to be the same as the framebuffer size in bytes.
        dbuf = make_unique<u8[]>(size);
        // Set function pointers to use the double buffer functions.
        setdbufptrs();
    } else
        // Set function pointers to use the direct framebuffer manipulation functions.
        setfbptrs();
}

// Set framebuffer pointers.
void fb::setfbptrs()
{
    get8p  = &fb::fbget8;
    get32p = &fb::fbget32;
    flipp  = &fb::nullflip;
    clearp = &fb::fbclear;
}

// Set double buffer pointers.
void fb::setdbufptrs()
{
    get8p  = &fb::dbufget8;
    get32p = &fb::dbufget32;
    flipp  = &fb::dbufflip;
    clearp = &fb::dbufclear;
}

// Unmap framebuffer from the system address space.
fb::~fb() 
{
    // Unmap framebuffer.
    if (munmap(fbp, size) < 0)
        die("Failed to unmap the framebuffer from the system's address space!");
}

// Set color value in the framebuffer.
void fb::set(const uint i, // Index to set the color value to.
             const pix& c) // Color to set.
{
    get32(i) = c.val(roff, goff, boff, aoff);
}

// Get size in bytes of the framebuffer.
size_t fb::len() const 
{
    return size;
}

// Get size in pixels of the framebuffer.
size_t fb::pixlen() const
{
    return plen;
}

#define CALLMEMBFN(p) (this->*(p))

// Access the buffer 8 bits/byte at a time.
u8& fb::get8(const uint i)       // Index beginning at 0 indexing a string of framebuffer bytes.
{
    return CALLMEMBFN(get8p)(i);
}

// Access the double buffer 8 bits/byte at a time.
u8& fb::dbufget8(const uint i)   // Index beginning at 0 indexing a string of framebuffer bytes.
{
    return dbuf[i];
}

// Access the frame buffer 8 bits/byte at a time.
u8& fb::fbget8(const uint i) // Index beginning at 0 indexing a string of framebuffer bytes.
{
    return fbp[i];
}

// Access memory 32 bits/4 bytes at a time.
u32& fb::get32(const uint i) // Index beginning at 0 indexing a string of framebuffer bytes. 
{
    return CALLMEMBFN(get32p)(i);
}

// Access the double buffer memory 32 bits/4 bytes at a time.
u32& fb::dbufget32(const uint i) // Index beginning at 0 indexing a string of framebuffer bytes. 
{
    return *(rcast<u32*>(&dbuf[0]) + i);
}

// Access framebuffer memory 32 bits/4 bytes at a time.
u32& fb::fbget32(const uint i) // Index beginning at 0 indexing a string of framebuffer bytes. 
{
    return *(rcast<u32*>(&fbp[0]) + i);
}

// Copy provided buffer to this framebuffer.
void fb::copy(const uint   i,   // Index indexing into the buffer array of bytes.
              const char  *buf, // Pointer to the buffer array itself.
              const size_t len) // Length/size of the buffer in bytes.
{
    memcpy(&dbuf[i], buf, len);
}

// Wait for vertical sync.
void fb::vsync()
{
    // Try waiting for vertical sync.
    try {
        sc.vsync();
    } catch (const err& e) {
        // Disable vertical sync, because it is not supported.
        vsyncen = false;
        throw;
    }
}

// Flip between two buffers, thus reduce tearing.
void fb::flip()
{
    CALLMEMBFN(flipp)();
}

// Double buffer flip.
void fb::dbufflip()
{
    // Blit by copying the double buffer into the framebuffer.
    if (sc.dbufen) {
        sc.flip();
        // TODO: Change pointer.
        return;
    }

    // Wait for vertical sync before copying.
    this->vsync();
    // Copy double buffer into the framebuffer.
    memcpy(fbp, &dbuf[0], size);
}

// Do no flip if manipulating directly to framebuffer.
void fb::nullflip() {}

// Clear/blacken the entire screen.
void fb::clear()
{
    CALLMEMBFN(clearp)();
}

// Double-buffered clear.
void fb::dbufclear()
{
    memset(&dbuf[0], 0, size);
}

// Clear framebuffer directly.
void fb::fbclear()
{
    memset(&fbp[0], 0, size);
}
