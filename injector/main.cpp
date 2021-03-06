#define BUILD_DLL
#include "main.h"
#include <iostream>

typedef BOOL (WINAPI *SETWINDOWPOS)		(HWND, HWND, int, int, int, int, UINT);

SETWINDOWPOS pMySetWindowPos;

BOOL (__cdecl *HookFunction)			(ULONG_PTR OriginalFunction, ULONG_PTR NewFunction);
VOID (__cdecl *UnhookFunction)			(ULONG_PTR Function);
ULONG_PTR (__cdecl *GetOriginalFunction)(ULONG_PTR Hook);

DWORD _p_ptempbuffer = 2;

void DLL_EXPORT Init()
{
	return;
}

volatile BOOL DLL_EXPORT MySetWindowPos(HWND h1, HWND h2, int i1, int i2, int i3, int i4, UINT u1)
{
	__asm
	{
		push u1
		push i4
		push i3
		push i2
		push i1
		push h2
		push h1

		cmp [_p_ptempbuffer], 2
		je _n

		cmp edi, 0x00000001
		je _t

	_n:
		mov [_p_ptempbuffer], esp
		add [_p_ptempbuffer], 0x1C

		call pMySetWindowPos

	_t:
		cmp [_p_ptempbuffer], 2
		je _v

		mov esp, [_p_ptempbuffer]
		mov [_p_ptempbuffer], 2
	_v:
		mov eax, 1
	}
}

int DLL_EXPORT GetSetWindowPos(void *p)
{
	// this function must be called before setting the hook to provide the hooking function with the bridge address
	pMySetWindowPos = (SETWINDOWPOS)p;
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	std::cout << "patching app" << std::endl;
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
        {
			pMySetWindowPos = NULL;
			GetSetWindowPos(SetWindowPos);

			HMODULE hHookEngineDll	= LoadLibrary(L"NtHookEngine.dll");
			
			HookFunction			= (BOOL (__cdecl *)(ULONG_PTR, ULONG_PTR))	GetProcAddress(hHookEngineDll, "HookFunction");
			UnhookFunction			= (VOID (__cdecl *)(ULONG_PTR))				GetProcAddress(hHookEngineDll, "UnhookFunction");
			GetOriginalFunction		= (ULONG_PTR (__cdecl *)(ULONG_PTR))		GetProcAddress(hHookEngineDll, "GetOriginalFunction");
			
			if (HookFunction == NULL || UnhookFunction == NULL || GetOriginalFunction == NULL)
				return 0;

			HookFunction((ULONG_PTR) GetProcAddress(LoadLibrary(L"User32.dll"), "SetWindowPos"), (ULONG_PTR) &MySetWindowPos);
			pMySetWindowPos = (SETWINDOWPOS)GetOriginalFunction((ULONG_PTR)MySetWindowPos);
			std::cout << "host application patched" << std::endl;
			break;
		}
        case DLL_PROCESS_DETACH:
			UnhookFunction((ULONG_PTR) GetProcAddress(LoadLibrary(L"User32.dll"), "SetWindowPos"));
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
            break;
    }
    return TRUE; // succesful
}