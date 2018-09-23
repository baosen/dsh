#include <vector>
#include <cstring>
#include <sys/mman.h>
#include "fb.hpp"
#include "log.hpp"
using namespace std;

// Double buffer for tear-free framebuffer manipulation.
static std::vector<u8> dbuf; 

// Setup framebuffer file mapping to the address space.
fb::fb() 
    : roff(-1), goff(-1), boff(-1), aoff(-1) // Blanken color offsets.
{
    // Check if we can double buffer by doubling the height of the virtual screen.
    if (sc.pageen) {
        // Get size of framebuffer in bytes and half it to accommedate for the virtual screen.
        size  = sc.finfo().smem_len / 2;
        // Set function pointers to use the direct framebuffer manipulation functions.
        setfbptrs();
        // Use the double-height framebuffer swap for no tearing.
        flipp = &fb::scrflip;
    } else if (sc.isvsync()) { // Double buffer on vertical sync.
        // Get size of the framebuffer in bytes.
        size = sc.finfo().smem_len;
        // Set size of the double buffer to be the same as the framebuffer size in bytes.
        dbuf.resize(size);
        // Set function pointers to use the double buffer functions.
        setdbufptrs();
    } else { // Manipulate framebuffer directly.
        // Get size of the framebuffer in bytes.
        size = sc.finfo().smem_len;
        // Set function pointers to use the direct framebuffer manipulation functions.
        setfbptrs();
        // Use framebuffer directly.
        flipp = &fb::nullflip;
    }

    // Compute number of pixels.
    plen = size / sizeof(u32);

    // Map framebuffer to computer's address space.
    fbp = scast<u8*>(mmap(nullptr,                // Offset.
                          size,                   // Size of memory.
                          PROT_READ | PROT_WRITE, // Read and write access!
                          MAP_SHARED,             // Shared memory.
                          sc.fd,                  // File descriptor to put it.
                          0));                    // ???.

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

// Set framebuffer pointers.
void fb::setfbptrs()
{
    get8p  = &fb::fbget8;
    get32p = &fb::fbget32;
    clearp = &fb::fbclear;
}

// Set double buffer pointers.
// NOTICE: Using this, the buffer gets remade each time it is opened and cleared on destruction.
void fb::setdbufptrs()
{
    get8p  = &fb::dbufget8;
    get32p = &fb::dbufget32;
    flipp  = &fb::vsyncflip;
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
    if (i >= size)
        throw err("Indexing outside framebuffer boundary!");

    return fbp[i];
}

// Access memory 32 bits/4 bytes at a time.
u32& fb::get32(const uint i) // Index beginning at 0 indexing a string of framebuffer bytes. 
{
    if (i >= plen)
        throw err("Indexing outside framebuffer boundary!");

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

// Flip between two buffers, thus reduce tearing.
void fb::flip()
{
    CALLMEMBFN(flipp)();
}

// Flip "double screen".
void fb::scrflip()
{
    sc.flip();
}

// Flip double buffer on vertical sync.
void fb::vsyncflip()
{
    // Wait for vertical sync before copying.
    sc.vsync();

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
