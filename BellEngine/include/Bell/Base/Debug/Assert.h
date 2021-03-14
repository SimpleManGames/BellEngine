#ifndef __ASSERT_H__
#define __ASSERT_H__

#include "Bell/Base/Core.h"
#include "Bell/Base/Log.h"

// TODO: Create a macro for no arguments other than the condition
#ifdef B_ENABLE_ASSERTS
#define B_ASSERT(x, ...)                                   \
    {                                                      \
        if (!(x))                                          \
        {                                                  \
            B_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
            __debugbreak();                                \
        }                                                  \
    }
#define B_CORE_ASSERT(x, ...)                                   \
    {                                                           \
        if (!(x))                                               \
        {                                                       \
            B_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
            __debugbreak();                                     \
        }                                                       \
    }
#else
#define B_ASSERT(x, ...)
#define B_CORE_ASSERT(x, ...)
#endif // B_ENABLE_ASSERTS

#endif // __ASSERT_H__