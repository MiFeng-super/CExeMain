# CExeMain
让 EXE 也拥有 DllMain

# 支持
x64 x32

# 实时方法
替换 LDR_DATA_TABLE_ENTRY 中的 EntryPoint。具体看完整源码。
```cpp
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
```
