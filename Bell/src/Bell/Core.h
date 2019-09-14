// Core Defines
// ------------

#ifndef CORE_H
#define CORE_H

#include <memory>

#define PLATFORM_WINDOWS 1
#define PLATFORM_MAC 2
#define PLATFORM_UNIX 3

#if defined(_WIN32)
#define B_PLATFORM PLATFORM_WINDOWS
#elif defined(__APPLE__)
#define B_PLATFORM PLATFORM_MAC
#error Bell only supports Windows
#else
#define B_PLATFORM PLATFORM_UNIX
#error Bell only supports Windows
#endif // Operator Defitions

#if B_PLATFORM == PLATFORM_WINDOWS
#if B_DYNAMIC_LINK
#ifdef B_BUILD_DLL
#define BELL_API __declspec(dllexport)
#else
#define BELL_API __declspec(dllimport)
#endif // !B_BUILD_DLL
#else
#define BELL_API 
#endif // !B_DYNAMIC_LINK
#else
#error Bell only Supports Windows
#endif // !B_PLATFORM_WINDOWS

#ifdef B_DEBUG
#define B_ENABLE_ASSERTS
#endif // B_DEBUG

#ifdef B_ENABLE_ASSERTS
#define B_ASSERT(x, ...) { if (!(x)) { B_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define B_CORE_ASSERT(x, ...) { if (!(x)) { B_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define B_ASSERT(x, ...)
#define B_CORE_ASSERT(x, ...)
#endif // B_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define B_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Bell
{
    /// Pre-defining types for changing later for ease of interation
    ///

    template<typename T>
    using Scope = std::unique_ptr<T>;
 
    template<typename T>
    using Ref = std::shared_ptr<T>;
}

#endif // !CORE_H