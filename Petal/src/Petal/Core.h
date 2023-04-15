#pragma once

#ifdef PTL_PLATFORM_WINDOWS
	#ifdef PTL_BUILD_DLL
		#define PTL_API __declspec(dllexport)
	#else
		#define PTL_API __declspec(dllimport)
	#endif
#else
	#error Petal only supports Windows!
#endif

#ifdef PTL_ENABLE_ASSERTS
	#define PTL_ASSERT(x, ...) { if(!(x)) { PTL_CRITICAL("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define PTL_CORE_ASSERT(x, ...) { if(!(x)) { PTL_CORE_CRITICAL("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define PTL_ASSERT(x, ...)
	#define PTL_CORE_ASSERT(x, ...)
#endif

#define PTL_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)