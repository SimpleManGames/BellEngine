#ifndef __ASSERT_H__
#define __ASSERT_H__

#include "Bell/Base/Core.h"
#include "Bell/Base/Log.h"
#include <filesystem>

#ifdef B_ENABLE_ASSERTS

// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define B_INTERNAL_ASSERT_IMPL(type, check, msg, ...) \
    {                                                 \
        if (!(check))                                 \
        {                                             \
            B##type##ERROR(msg, __VA_ARGS__);         \
            B_DEBUGBREAK();                           \
        }                                             \
    }
#define B_INTERNAL_ASSERT_WITH_MSG(type, check, ...) B_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define B_INTERNAL_ASSERT_NO_MSG(type, check) B_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", B_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define B_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define B_INTERNAL_ASSERT_GET_MACRO(...) B_EXPAND_MACRO(B_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, B_INTERNAL_ASSERT_WITH_MSG, B_INTERNAL_ASSERT_NO_MSG))

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define B_ASSERT(...) B_EXPAND_MACRO(B_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__))
#define B_CORE_ASSERT(...) B_EXPAND_MACRO(B_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__))

#else

#define B_ASSERT(x, ...)
#define B_CORE_ASSERT(x, ...)

#endif // B_ENABLE_ASSERTS

#endif // __ASSERT_H__