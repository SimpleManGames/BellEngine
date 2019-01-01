#ifndef CORE_H
#define CORE_H

#ifdef B_PLATFORM_WINDOWS
#ifdef B_BUILD_DLL
#define BELL_API __declspec(dllexport)
#else
#define BELL_API __declspec(dllimport)
#endif
#else
#error Bell only Supports Windows
#endif

#ifdef B_ENABLE_ASSERT
#define B_ASSERT(x, ...) { if (!(x)) { BL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define B_CORE_ASSERT(x, ...) { if (!(x)) { BL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define B_ASSERT(x, ...)
#define B_CORE_ASSERT(x, ...)
#endif // B_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#endif // !CORE_H