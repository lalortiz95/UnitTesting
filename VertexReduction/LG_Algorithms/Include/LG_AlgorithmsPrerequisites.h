#pragma once


#if defined(LG_ALGORITHMS_EXPORTS)
#	define LG_ALGORITHMS_EXPORT __declspec(dllexport)
#elif defined(LG_ALGORITHMS_STATIC)
#	define LG_ALGORITHMS_EXPORT 
#else
#	define LG_ALGORITHMS_EXPORT __declspec(dllimport)
#endif