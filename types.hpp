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
typedef char           byte;

#define scast          static_cast
#define rcast          reinterpret_cast 
#define ccast          const_cast 
#define forever        for (;;)

using err =            std::runtime_error;
