#pragma once
#include <cstdint>
#include <stdexcept>

typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef uint32_t       u32;
typedef int32_t        s32;
typedef uint8_t        u8;
typedef int8_t         s8;

static_assert(sizeof(char) == 1, "char is not a single byte on this compiler!");
typedef char           byte;

#define scast          static_cast
#define rcast          reinterpret_cast 
#define ccast          const_cast 
#define forever        for (;;)

using err =            std::runtime_error;

// Get the size of an array.
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
// Tell the compiler which variables is unused.
#define UNUSED(expr) do { (void)(expr); } while (0)
