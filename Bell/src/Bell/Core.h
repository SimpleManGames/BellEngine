#pragma once

#ifdef BZ_PLATFORM_WINDOWS
	#ifdef BZ_BUILD_DLL
		#define BELL_API __declspec(dllexport)
	#else
		#define BELL_API __declspec(dllimport)
	#endif
#else
	#error Bell only Supports Windows
#endif