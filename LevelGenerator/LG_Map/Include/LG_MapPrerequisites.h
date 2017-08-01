#pragma once

#include <LG_GeometryPrerequisites.h>
#include <LG_UtilitiesPrerequisites.h>


#if defined(LG_MAP_EXPORTS)
#	define LG_MAP_EXPORT __declspec(dllexport)
#elif defined(LG_MAP_STATIC)
#	define LG_MAP_EXPORT 
#else
#	define LG_MAP_EXPORT __declspec(dllimport)
#endif