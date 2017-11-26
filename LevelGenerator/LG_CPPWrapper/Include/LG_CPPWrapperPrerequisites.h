#pragma once
#include <LG_UtilitiesPrerequisites.h>
#include <LG_GeometryPrerequisites.h>
#include <LG_MapPrerequisites.h>
#include <LG_AlgorithmsPrerequisites.h>

#if defined(LG_WRAPPER_EXPORTS)
#	define LG_WRAPPER_EXPORT __declspec(dllexport)
#elif defined(LG_WRAPPER_STATIC)
#	define LG_WRAPPER_EXPORT 
#else
#	define LG_WRAPPER_EXPORT __declspec(dllimport)
#endif