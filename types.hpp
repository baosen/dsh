#pragma once
#include <cstdint>
#include <stdexcept>
typedef unsigned int uint;
typedef uint32_t u32;
typedef int32_t s32;
#define static_cast scast
#define reinterpret_cast rcast
#define const_cast ccast
#define forever for(;;)
using err = std::runtime_error;
