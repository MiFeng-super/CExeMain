#include "CExeMain.h"

CExeMain::CExeMain() 
{

}

CExeMain::~CExeMain() 
{
	if (m_OldMain && m_hModule)
	{
		LdrSetEntryPoint(m_hModule, m_OldMain);
		m_NewMain(m_hModule, DLL_PROCESS_DETACH, 0);

		m_OldMain = 0;
		m_NewMain = 0;
	}
}

bool CExeMain::Init(LPEXEMAIN NewMain)
{
	m_hModule = LoadLibrary(L"Version.dll");
	if (m_hModule)
	{
		m_NewMain = NewMain;
		m_OldMain = (LPEXEMAIN)LdrSetEntryPoint(m_hModule, m_NewMain);
		if (m_OldMain)
		{
			m_NewMain(m_hModule, DLL_PROCESS_ATTACH, 0);
			return true;
		}
	}

	return false;
}

BOOL CExeMain::DllMain(HMODULE hModule, DWORD fdwReason, LPVOID lpvReserved) 
{
	if (m_OldMain == NULL || fdwReason == DLL_PROCESS_ATTACH)
	{
		return TRUE;
	}
	return m_OldMain(hModule, fdwReason, lpvReserved);
}

PVOID __stdcall LdrSetEntryPoint(HMODULE hModule, PVOID EntryPoint)
{
	PPEB_LDR_DATA Ldr = NtCurrentTeb()->ProcessEnvironmentBlock->Ldr;

	PLIST_ENTRY pHeadList = &Ldr->InMemoryOrderModuleList;
	PLIST_ENTRY pCurrList = pHeadList->Flink;

	PVOID OldEntryPoint = NULL;

	while (pHeadList != pCurrList)
	{
		PLDR_DATA_TABLE_ENTRY pLdrDataEntry = 
			(PLDR_DATA_TABLE_ENTRY)CONTAINING_RECORD(pCurrList, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

		if (pLdrDataEntry->DllBase == hModule)
		{
			OldEntryPoint = pLdrDataEntry->EntryPoint;
			pLdrDataEntry->EntryPoint = EntryPoint;
			break;
		}

		pCurrList = pCurrList->Flink;
	}

	return OldEntryPoint;
}
