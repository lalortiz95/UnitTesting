#pragma once

#if defined(LG_EXPORTS)
#	define LG_EXPORT __declspec(dllexport)
#elif defined(LG_STATIC)
#	define LG_EXPORT 
#else
#	define LG_EXPORT __declspec(dllimport)
#endif