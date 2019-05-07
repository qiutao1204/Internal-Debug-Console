#include "stdafx.h"
#include <Windows.h>
#include <iostream>
 
// proof https://i.imgur.com/YzJYm70.png

void CreateConsole(LPCSTR yes)
{
	DWORD OldProtect;
	VirtualProtect((LPVOID)&FreeConsole, 1, PAGE_EXECUTE_READWRITE, &OldProtect);
	*(BYTE*)(&FreeConsole) = 0xC3;
	VirtualProtect((LPVOID)&FreeConsole, 1, OldProtect, &OldProtect);
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	SetConsoleTitleA(yes);
}

int Main() {
	CreateConsole("Internal Debug Console");
	printf("hello! \n");
	return 1;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);

		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Main, 0, 0, 0);
		break;
	}
	return TRUE;
}