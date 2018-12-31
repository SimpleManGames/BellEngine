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

#define BIT(x) (1 << x)

// Header Guard
#endif