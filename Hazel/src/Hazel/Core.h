#pragma once

#ifdef HZ_PLATFORM_WINDOWS
	#ifdef HZ_BUILE_DLL
		#define HAZEL_API __declspec(dllexport)
	#else 
		#define HAZEL_API __declspec(dllimport)
	#endif
#else
	#error Hazel only support Windows!
#endif // HZ_PLATFORM_ WINDOWS
