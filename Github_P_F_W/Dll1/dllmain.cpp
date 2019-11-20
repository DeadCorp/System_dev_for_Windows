// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include "Windows.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
extern "C" _declspec(dllexport) UINT elipsR(HDC hdc,int x,int y,int z,int v)
{
	return Ellipse(hdc, x,y,z,v);
}
extern "C" _declspec(dllexport) UINT kvadratR(HDC hdc, int x, int y, int z, int v)
{
	return Rectangle(hdc, x, y, z, v);
}
extern "C" _declspec(dllexport) UINT kvadratnokutR(HDC hdc, int x, int y, int z, int v,int s,int f)
{
	return RoundRect(hdc, x, y, z, v,s,f);
}

