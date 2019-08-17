//===========================================================//
// Name: platform.h
// Purpose: Platform stuff
// Date: 8/11/2019
//===========================================================//
#include "platform.h"

#ifdef _LINUX
#include <dlfcn.h>
#elif defined(_WINDOWS)
#include <Windows.h>
#endif

//-------------------------------------------------------//
// Load library and return handle
//-------------------------------------------------------//
HANDLE DLL_EXPORT Plat_LoadLibrary(const char* path)
{
	Assert(path != NULL);
#ifdef _WINDOWS

#else
	return dlopen(path, RTLD_LAZY);
#endif
}

//-------------------------------------------------------//
// Return pointer to symbol in library
//-------------------------------------------------------//
HANDLE DLL_EXPORT Plat_FindSymbol(HANDLE lib, const char* sym)
{
	Assert(lib != NULL);
	Assert(sym != NULL);
#ifdef _WINDOWS

#else
	return dlsym(lib, sym);
#endif
}

//-------------------------------------------------------//
// Closes a library
//-------------------------------------------------------//
void DLL_EXPORT Plat_CloseLibrary(HANDLE lib)
{
	Assert(lib != NULL);
#ifdef _WINDOWS

#else
	dlclose(lib);
#endif
}