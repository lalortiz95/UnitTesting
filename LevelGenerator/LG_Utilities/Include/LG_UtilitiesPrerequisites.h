#pragma once

#include "LG_UtilityMacro.h"
#include "LG_StdHeaders.h"
#include "LG_UtilityPlatformDefines.h"
#include "LG_UtilityPlatformTypes.h"

#if defined(LG_UTILITIES_EXPORTS)
#	define LG_UTILITIES_EXPORT __declspec(dllexport)
#elif defined(LG_UTILITIES_STATIC)
#	define LG_UTILITIES_EXPORT 
#else
#	define LG_UTILITIES_EXPORT __declspec(dllimport)
#endif