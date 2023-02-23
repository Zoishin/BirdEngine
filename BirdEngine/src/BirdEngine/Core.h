#pragma once


#ifdef BE_PLATFORM_WINDOWS
	#ifdef BE_BUILD_DLL
		#define BE_API __declspec(dllexport)
	#else
		#define BE_API __declspec(dllimport)
	#endif 

#else
	#error BirdEngine now only support windows!
#endif

#ifdef BE_ENABLE_ASSERTS
	#define BE_ASSERT(x, ...) {if((!x)) {BE_ERROR("Assert Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define BE_CORE_ASSERT(x, ...) {if((!x)) {BE_CORE_ERROR("Assertion Failed: {0]", __VA_ARGS__); __debugbreak()}}
#else
	#define BE_ASSERT(x, ...)
	#define BE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)