#pragma once
#ifdef PANGU_PLATFORM_WINDOWS
	#ifdef PANGU_BUILD_DLL
		#define PANGU_API __declspec(dllexport)
	#else
		#define PANGU_API __declspec(dllimport)
	#endif
#else
	#error PANGU only support for WINDOWS!
#endif // PANGU_PLATFORM_WINDOWS
