#pragma once

/************************************************************************/
/* SISTEMA OPERATIVO                                                    */
/************************************************************************/

#define LG_PLATFORM_WIN32 1
#define LG_PLATFORM_LINUX 2
#define LG_PLATFORM_OSX 3
#define LG_PLATFORM_PS4 4

/************************************************************************/
/* TIPO DE COMPILADOR                                                   */
/************************************************************************/

#define LG_COMPILER_MSVC 1
#define LG_COMPILER_GNUC 2
#define LG_COMPILER_INTEL 3
#define LG_COMPILER_CLANG 4

/************************************************************************/
/* ARQUITECTURA                                                         */
/************************************************************************/

#define LG_ARCHITECTURE_x86_32 1
#define LG_ARCHITECTURE_x86_64 2
#define LG_ARCHITECTURE_ARM 2

/************************************************************************/
/* ENDIANS                                                              */
/************************************************************************/

///Little Endian
#define LG_ENDIAN_LITTLE 1 
///Big Endian
#define LG_ENDIAN_BIG 2 

#define LG_ENDIAN LG_ENDIAN_LITTLE

#define LG_EDITOR_BUILD 1

/************************************************************************/
/* Modo: DEBUG, RELEASE, PROFILE                                        */
/************************************************************************/

#define LG_DEBUG_MODE 1
#define LG_RELEASE_MODE 2
#define LG_PROFILE_MODE 3

/************************************************************************/
/*                                                                      */
/************************************************************************/



/************************************************************************/
/* TIPO DE COMPILADOR Y VERSIÓN                                         */
/************************************************************************/
#if defined(_MSC_VER)
#define LG_COMPILER LG_COMPILER_MSVC
#define LG_COMP_VER _MSC_VER
#define LG_THREADLOCAL _declspec(thread)
#elif defined(__GNUC__)
#define LG_COMPILER LG_COMPILER_GNUC
#define LG_COMP_VER (((__GNUC__)*100) + (__GNUC_MINOR__*10) + __GNUC_PATCHLEVEL__)
#define LG_THREADLOCAL __thread
#elif defined(__INTEL_COMPILER)	
#define LG_COMPILER LG_COMPILER_INTEL
#define LG_COMP_VER __INTEL_COMPILER
#elif defined(__clang__)
#define LG_COMPILER LG_COMPILER_CLANG
#define LG_COMP_VER __clang_major__
#define LG_THREADLOCAL __thread
#else
#pragma error "no known compiler. "
#endif

/************************************************************************/
/* Ver si podemos usar __forceinline o si necesitamos __inline          */
/************************************************************************/
#if LG_COMPILER == LG_COMPILER_MSVC
#if LG_COMP_VER >= 1200
#define FORCEINLINE __forceinline
#ifndef RESTRICT
#define RESTRICT __restrict
#endif
#endif
#elif defined(__MINGW32__)
#if !defined(FORCEINLINE)
#define FORCEINLINE __inline
#ifndef RESTRICT
#define RESTRICT
#endif
#endif
#else
#define FORCEINLINE __inline
#ifndef RESTRICT
#define RESTRICT __restrict
#endif
#endif

/************************************************************************/
/* Encuentra la plataforma actual                                       */
/************************************************************************/
#if defined(__WIN32__) || defined(_WIN32) //Si es una plataforma de windows
#define LG_PLATFORM LG_PLATFORM_WIN32
#elif defined(__APLE_CC__)
#define LG_PLATFORM LG_PLATFORM_APPLE //Es una plataforma de apple
#elif defined(__ORBIS__)
#define LG_PLATFORM LG_PLATFORM_PS4 //Es una plataforma de PSVITA
#else
#define LG_PLATFORM LG_PLATFORM_LINUX //La tomaré como una plataforma de Linux
#endif

/************************************************************************/
/* Encuentra el tipo de arquitectura                                    */
/************************************************************************/
#if defined(__x86_64__) || defined(_M_X64)
#define LG_ARCH_TYPE LG_ARCHITECTURE_X86_64 //Si será una compilación de x64
#else
#define LG_ARCH_TYPE LG_ARCHITECTURE_X86_32 //Si será una compilación de x86
#endif

/************************************************************************/
/* Macros de memoria                                                    */
/************************************************************************/
#if LG_COMPILER == LG_COMPILER_MSVC
#define MS_ALIGN(n) __declspec(align(n))
#ifndef GCC_PACK
#define GCC_PACK(n)
#endif
#ifndef GCC_ALIGN
#define GCC_ALIGN(n)
#endif
#elif ( LG_COMPILER == LG_COMPILER_GNUC && LG_PLATFORM == LG_PLATFORM_PS4)
#define MS_ALIGN(n)
#define GCC_PACK(n)
#define GCC_ALIGN(n) __attribute__( (__aligned__(n)) )
#else
#define MS_ALIGN(n)
#define GCC_PACK(n) __attribute__( (packed, aligned(n)) )
#define GCC_ALIGN(n) __attribute__( (aligned(n)) )
#endif

/************************************************************************/
/* For throw override                                                   */
/************************************************************************/
#if LG_COMPILER == LG_COMPILER_MSVC
#define _NOEXCEPT noexcept
#elif LG_COMPILER == LG_COMPILER_INTEL
#define _NOEXCEPT noexcept
#elif LG_COMPILER == LG_COMPILER_GNUC
#define _NOEXCEPT noexcept
#else
#define _NOEXCEPT
#endif

/************************************************************************/
/* Propiedades específicas de windows                                   */
/************************************************************************/
//Definiciones para el manejo de la DLL
///ESTO ES MUY IMPORTANTE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#if LG_PLATFORM == LG_PLATFORM_WIN32
#if defined( LG_STATIC_LIB)
#define LG_UTILITY_EXPORT
#else
#if defined(LG_UTILITY_EXPORTS)
#define LG_UTILITY_EXPORT __declspec(dllexport)
#else
#if defined (__WINGW32__)
#define LG_UTILITY_EXPORT
#else
#define LG_UTILITY_EXPORT __declspec(dllimport)
#endif
#endif
#endif

#if defined(_DEBUG) || defined(DEBUG)
#define LG_DEBUG_MODE 1
#else 
#define LG_DEBUG_MODE 0
#endif

#if LG_COMPILER == LG_COMPILER_INTEL
#define LG_THREADLOCAL __declspec(thread)
#endif
#endif

/************************************************************************/
/* Propiedades específicas de Linux/Apple                               */
/************************************************************************/
#if LG_PLATFORM == LG_PLATFORM_LINUX || LG_PLATFORM == LG_PLATFORM_OSX
#if defined(LG_GCC_VISIBILITY)
#define LG_UTILITY_EXPORT __attribute__ ((visibility("default")))
#else
#define LG_UTILITY_EXPORT
#endif

#define stricmp strcasecmp

///Si estamos en un build tipo DEBUG
#if defined(_DEBUG) || defined(DEBUG)
#define LG_DEBUG_MODE 1
#else
#define LG_DEBUG_MODE 0
#endif

#if LG_COMPILER == LG_COMPILER_INTEL
#define LG_THREADLOCAL __thread
#endif
#endif

/************************************************************************/
/* Propiedades específicas del PSVITA                                   */
/************************************************************************/
#if LG_PLATFORM == LG_PLATFORM_PS4
#if defined(LG_STATIC_LIB)
#define LG_UTILITY_EXPORT
#else
#if defined(LG_UTILIY_EXPORTS)
#define LG_UTILITY_EXPORT __declspec(dllexport)
#else
#if defined (__WINGW32__)
#define LG_UTILITY_EXPORT
#else
#define LG_UTILITY_EXPORT __declspec(dllimport)
#endif
#endif
#endif

#if defined(_DEBUG) || defined(DEBUG)
#define LG_DEBUG_MODE 1
#else 
#define LG_DEBUG_MODE 0
#endif
#endif


/************************************************************************/
/* Definiciones de macros de debug                                      */
/************************************************************************/
#if LG_DEBUG_MODE
#define LG_DEBUG_ONLY(x) x
#define LG_ASSERT(x) assert(x)
#else
#define LG_DEBUG_ONLY(x)
#define LG_ASSERT(x)
#endif

/************************************************************************/
/* TIPO DE COMPILADOR Y VERSIÓN                                         */
/************************************************************************/

#ifdef _WINDOWS
#define LG_PLATFORM LG_PLATFORM_WIN32 //Estamos usando Windows
#endif // _WINDOWS

#ifdef __linux__
#define LG_PLATFORM_LINUX //Estamos usando Linux
#endif

#ifdef _PSVITA
#define LG_PLATFORM LG_PLATFORM_PSVITA //Estamos usando PSVITA
#endif