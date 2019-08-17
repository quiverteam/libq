//===========================================================//
// Name: platform.h
// Purpose: Platform stuff
// Date: 8/11/2019
//===========================================================//
#pragma once

/* some c standard includes that must be here */
#include <stddef.h>
#include <stdint.h>
#include <assert.h>

#ifdef _WIN32

#define FORCEINLINE __forceinline
#define INLINE inline
#define DLL_EXPORT __declspec(dllexport)
#define DLL_IMPORT __declspec(dllimport)
#define FORCE_EMIT		__attribute__((used)) /* Used to force emit a variable even if unused */
#define VECTOR(x)		__attribute__((vector_size(x)))
#define VECTOR2			VECTOR(2)
#define VECTOR4			VECTOR(4)
#define VECTOR8			VECTOR(8)
#define VECTOR16		VECTOR(16)
#define VECTOR32		VECTOR(32)
#define VECTOR64		VECTOR(64)

#elif defined(__GNUC__)

#define FORCEINLINE 	__attribute__((always_inline))
#define INLINE 			inline
#define DLL_EXPORT		__attribute__((visibility("default")))
#define DLL_IMPORT
#define FORCE_EMIT		__attribute__((used)) /* Used to force emit a variable even if unused */
#define VECTOR(x)		__attribute__((vector_size(x)))
#define VECTOR2			VECTOR(2)
#define VECTOR4			VECTOR(4)
#define VECTOR8			VECTOR(8)
#define VECTOR16		VECTOR(16)
#define VECTOR32		VECTOR(32)
#define VECTOR64		VECTOR(64)

#endif

#define ALIGN(x)		alignas(x)
#define ALIGN2			ALIGN(2)
#define ALIGN4			ALIGN(4)
#define ALIGN8			ALIGN(8)
#define ALIGN16			ALIGN(16)
#define ALIGN32			ALIGN(32)
#define ALIGN64			ALIGN(64)

#ifndef NDEBUG
#define Assert(cond)		assert((cond))
#define AssertMsg(cond, msg) assert((cond))
#else
#define Assert(cond)
#define AssertMsg(cond, msg)
#endif

/* Release build assert */
#define RelAssert(cond)	assert(cond)

/* To make C code nicer? */
#define BEGIN_C_BLOCK extern "C" {
#define END_C_BLOCK }

/* Some stupid aliases */
typedef uint16_t ushort;
typedef uint32_t uint;
typedef uint64_t ulong;

/* Less dumb aliases */
typedef int8_t 		i8;
typedef uint8_t 	u8;
typedef int16_t 	i16;
typedef uint16_t 	u16;
typedef int32_t 	i32;
typedef uint32_t 	u32;
typedef int64_t 	i64;
typedef uint64_t 	u64;
typedef float		f32;
typedef double		f64;
typedef long double	f80;

/* Windows portability stuff (kinda) */
#define BOOL	int
#define TRUE	1
#define FALSE	0

typedef void* HANDLE;

//-------------------------------------------------------//
// Load library and return handle
//-------------------------------------------------------//
HANDLE DLL_EXPORT Plat_LoadLibrary(const char* path);

//-------------------------------------------------------//
// Return pointer to symbol in library
//-------------------------------------------------------//
HANDLE DLL_EXPORT Plat_FindSymbol(HANDLE lib, const char* sym);

//-------------------------------------------------------//
// Closes a library
//-------------------------------------------------------//
void DLL_EXPORT Plat_CloseLibrary(HANDLE lib);