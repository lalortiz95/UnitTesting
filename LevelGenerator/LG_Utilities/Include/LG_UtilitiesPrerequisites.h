#pragma once

#if defined(LG_UTILITIES_EXPORTS)
#	define LG_UTILITIES_EXPORT __declspec(dllexport)
#elif defined(LG_UTILITIES_STATIC)
#	define LG_UTILITIES_EXPORT 
#else
#	define LG_UTILITIES_EXPORT __declspec(dllimport)
#endif