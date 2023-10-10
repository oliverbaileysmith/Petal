#pragma once

#include <memory>

#ifndef PTL_PLATFORM_WINDOWS
	#error Petal only supports Windows!
#endif // PTL_PLATFORM_WINDOWS

#ifdef PTL_ENABLE_ASSERTS
	#define PTL_ASSERT(x, ...)                                      \
		{                                                           \
			if (!(x))                                               \
			{                                                       \
				PTL_CRITICAL("Assertion failed: {0}", __VA_ARGS__); \
				__debugbreak();                                     \
			}                                                       \
		}
	#define PTL_CORE_ASSERT(x, ...)                                      \
		{                                                                \
			if (!(x))                                                    \
			{                                                            \
				PTL_CORE_CRITICAL("Assertion failed: {0}", __VA_ARGS__); \
				__debugbreak();                                          \
			}                                                            \
		}
#else
	#define PTL_ASSERT(x, ...)
	#define PTL_CORE_ASSERT(x, ...)
#endif // PTL_ENABLE_ASSERTS

#define PTL_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace ptl
{
	template<typename T> using Scope = std::unique_ptr<T>;

	template<typename T> using Ref = std::shared_ptr<T>;
} // namespace ptl
