#pragma once

#define BIT(x) (1 << x)

#ifdef HZ_PLATFORM_WINDOWS
#if HZ_DYNAMIC_LINK
	#ifdef HZ_BUILD_DLL
		#define HAZEL_API __declspec(dllexport)
	#else 
		#define HAZEL_API __declspec(dllimport)
	#endif
#else
	#define HAZEL_API
#endif
#else
	#error Hazel only support Windows!
#endif // HZ_PLATFORM_ WINDOWS

#ifdef HZ_DEBUG
	#define HZ_ENABLE_ASSERTS
#endif //如果处于HZ_DEBUG模式下、启用HZ_ENABLE_ASSERTS

#ifdef HZ_ENABLE_ASSERTS
	#define HZ_ASSERT(x, ...) { if(!(x)) { HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define HZ_CORE_ASSERT(x, ...) { if(!(x)) { HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define HZ_ASSERT(x, ...)
	#define HZ_CORE_ASSERT(x, ...)
#endif

#define HZ_BIND_EVENT_FN(fn) std::bind(&fn,this,std::placeholders::_1)