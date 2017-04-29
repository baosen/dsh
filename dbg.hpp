#pragma once
#if !defined(NDEBUG)
#   define DBG(...) printf(__VA_ARGS__);
#else
#   define DBG(...)
#endif
