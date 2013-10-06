#ifndef __MAIN_H__
#define __MAIN_H__

#include <windows.h>

/*  To use this exported function of dll, include this header
 *  in your project.
 */

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport) WINAPI
#else
    #define DLL_EXPORT __declspec(dllimport) WINAPI
#endif


#ifdef __cplusplus
extern "C"
{
#endif
	void DLL_EXPORT Init();
#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__