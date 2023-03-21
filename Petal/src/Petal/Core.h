#pragma once

#ifdef PTL_PLATFORM_WINDOWS
	#ifdef PTL_BUILD_DLL
		#define PTL_API __declspec(dllexport)
	#else
		#define PTL_API __declspec(dllimport)
	#endif
#else
	#error Petal only supports windows!
#endif