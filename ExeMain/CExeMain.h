#pragma once
#include "ntdll.h"

typedef BOOL(WINAPI* LPEXEMAIN)(_In_ HMODULE hModule, _In_ DWORD fdwReason, _In_ LPVOID lpvReserved);

PVOID __stdcall LdrSetEntryPoint(HMODULE hModule, PVOID EntryPoint);

class CExeMain
{
public:
	CExeMain();
	~CExeMain();

private:
	HMODULE m_hModule;
	LPEXEMAIN m_NewMain;
	LPEXEMAIN m_OldMain;

public:
	bool Init(LPEXEMAIN NewMain);
	BOOL DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpvReserved);
};

