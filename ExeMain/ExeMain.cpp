// ExeMain.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>

#include "CExeMain.h"

CExeMain ExeMain;

BOOL WINAPI MyExeMain(_In_ HMODULE hModule, _In_ DWORD fdwReason, _In_ LPVOID lpvReserved) 
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		printf("DLL_PROCESS_ATTACH\n");
		break;

	case DLL_PROCESS_DETACH:
		printf("DLL_PROCESS_DETACH\n");
		break;

	case DLL_THREAD_ATTACH:
		printf("DLL_THREAD_ATTACH\n");
		break;

	case DLL_THREAD_DETACH:
		printf("DLL_THREAD_DETACH\n");
		break;
	}
	return ExeMain.DllMain(hModule, fdwReason, lpvReserved);
}

DWORD WINAPI ThreadProc(LPVOID lpThreadParameter) 
{
	return 0;
}

int main()
{
    ExeMain.Init(MyExeMain);

	CreateThread(NULL, NULL, ThreadProc, NULL, NULL, NULL);

    getchar();
    return 0;
}

