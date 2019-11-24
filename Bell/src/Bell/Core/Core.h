// Core Defines
// ------------

#ifndef _CORE_H
#define _CORE_H

#include <memory>

// Platform detection using predefined macros
#ifdef _WIN32
    /* Windows x64/x86 */
#ifdef _WIN64
    /* Windows x64  */
#define B_PLATFORM_WINDOWS
#else
    /* Windows x86 */
#error "x86 Builds are not supported!"
#endif
#elif defined(__APPLE__) || defined(__MACH__)
#include <TargetConditionals.h>
/* TARGET_OS_MAC exists on all the platforms
 * so we must check all of them (in this order)
 * to ensure that we're running on MAC
 * and not some other Apple platform */
#if TARGET_IPHONE_SIMULATOR == 1
#error "IOS simulator is not supported!"
#elif TARGET_OS_IPHONE == 1
#define B_PLATFORM_IOS
#error "IOS is not supported!"
#elif TARGET_OS_MAC == 1
#define B_PLATFORM_MACOS
#error "MacOS is not supported!"
#else
#error "Unknown Apple platform!"
#endif
 /* We also have to check __ANDROID__ before __linux__
  * since android is based on the linux kernel
  * it has __linux__ defined */
#elif defined(__ANDROID__)
#define B_PLATFORM_ANDROID
#error "Android is not supported!"
#elif defined(__linux__)
#define B_PLATFORM_LINUX
#error "Linux is not supported!"
#else
    /* Unknown compiler/platform */
#error "Unknown platform!"
#endif // End of platform detection

#ifdef B_DEBUG
#define B_ENABLE_ASSERTS
#define B_ENABLE_PROFILING
#endif // B_DEBUG

#ifdef B_ENABLE_ASSERTS
#define B_ASSERT(x, ...) { if (!(x)) { B_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define B_CORE_ASSERT(x, ...) { if (!(x)) { B_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define B_ASSERT(x, ...)
#define B_CORE_ASSERT(x, ...)
#endif // B_ENABLE_ASSERTS

#ifdef B_ENABLE_PROFILING
#include "Bell/Core/Profiler/InstrumentatonTimer.h"

#define B_PROFILER_BEGIN(name) Bell::Instrumentor::Get().BeginSession(name)
#define B_PROFILER_BEGIN(name, filePath) Bell::Instrumentor::Get().BeginSession(name, filePath)
#define B_PROFILER_END() Bell::Instrumentor::Get().EndSession();

#define B_PROFILE_SCOPE(name) Bell::InstrumentationTimer timer##__LINE__(name)
#define B_PROFILE_FUNCTION() B_PROFILE_SCOPE(__FUNCSIG__)
#else
#define B_PROFILER_BEGIN(name)
#define B_PROFILER_BEGIN(name, filePath)
#define B_PROFILER_END()

#define B_PROFILE_SCOPE(name)
#define B_PROFILE_FUNCTION()
#endif // B_ENABLE_PROFILING

#define BIT(x) (1 << x)

#define B_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Bell
{
    /// Pre-defining types for changing later for ease of interation
    ///

    template<typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
 
    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}

#endif // !_CORE_H