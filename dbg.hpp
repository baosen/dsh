#pragma once
#ifdef NDEBUG
#   define DBGPRINTF(...) printf(__VA_ARGS__);
#else
#   define DBGPRINTF(...)
#endif
