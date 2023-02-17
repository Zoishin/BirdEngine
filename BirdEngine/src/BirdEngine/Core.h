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