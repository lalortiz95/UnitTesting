#pragma once
#include <LG_UtilitiesPrerequisites.h>

#if defined(LG_GEOMETRY_EXPORTS)
#	define LG_GEOMETRY_EXPORT __declspec(dllexport)
#elif defined(LG_GEOMETRY_STATIC)
#	define LG_GEOMETRY_EXPORT 
#else
#	define LG_GEOMETRY_EXPORT __declspec(dllimport)
#endif