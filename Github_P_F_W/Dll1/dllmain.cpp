// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include "Windows.h"
#include "Math.h"

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
extern "C" _declspec(dllexport) UINT stepin(int x,int y)
{
	return pow(x,y);
}
extern "C" _declspec(dllexport) UINT factorial(int x,int y = 0)
{
	if (x < 0) // если пользователь ввел отрицательное число
		return 0; // возвращаем ноль
	if (x == 0) // если пользователь ввел ноль,
		return 1; // возвращаем факториал от нуля - не удивляетесь, но это 1 =)
	else // Во всех остальных случаях
		return x * factorial(x - 1); // делаем рекурсию.
}


