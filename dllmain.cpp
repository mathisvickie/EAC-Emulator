#include <Windows.h>
#include "D:\work\SDK\Utils.h"

class EAC_VirtualFunctions
{
public:
	virtual void RegisterInitCallbacks(void* clbk0, void* clbk1, void* p_g_hEAC) = 0;
	virtual void Unload(void) = 0;
	virtual void Initialize(void) = 0;
	virtual bool DoSomeChecks(void* ptr1, void* ptr2) = 0;
	virtual void UnkVirtFunc_0x20(void* unk1, int unk2) = 0; //not sure with return type
	virtual void RegisterUnkCallback(void* FuncCallback, int unk_Flags, void* unk_pObject) = 0;
	virtual void UnkVirtFunc_0x30() = 0;
	virtual void UnkVirtFunc_0x38() = 0;
	virtual void UnkVirtFunc_0x40() = 0;
	virtual void UnkVirtFunc_0x48() = 0;
	virtual void UnkVirtFunc_0x50(int unk1, int unk2) = 0;
};

class EAC_Interface : public EAC_VirtualFunctions
{
public:
	void RegisterInitCallbacks(void* clbk0, void* clbk1, void* p_g_hEAC)
	{
		return; //clbk0 = xor eax,eax; ret; & clbk1 = ret; so really does not matter if we call them or not
	}
	void Unload(void)
	{
		return;
	}
	void Initialize(void)
	{
		return;
	}
	bool DoSomeChecks(void* ptr1, void* ptr2)
	{
		return false; //if returned false then called only once, otherwise called in a loop until returned false
	}
	void UnkVirtFunc_0x20(void* unk1, int unk2)
	{
		return;
	}
	void RegisterUnkCallback(void* clbk, int unk_Flags, void* unk_pObject)
	{
		return; //clbk directly calls some virt func, lets better not call it
	}
	void UnkVirtFunc_0x30()
	{
		return;
	}
	void UnkVirtFunc_0x38()
	{
		return;
	}
	void UnkVirtFunc_0x40()
	{
		return;
	}
	void UnkVirtFunc_0x48()
	{
		return;
	}
	void UnkVirtFunc_0x50(int unk1, int unk2)
	{
		return;
	}
};

void* CreateGameClient(char* szInterfaceNameWithVersion)
{
	return (new EAC_Interface);
}

typedef HMODULE(*fnLoadLibraryExW)(LPCWSTR, HANDLE, DWORD);
fnLoadLibraryExW oLoadLibraryExW;

typedef LPVOID(*fnGetProcAddress)(HMODULE, LPCSTR);
fnGetProcAddress oGetProcAddress;

HMODULE g_hMod;

HMODULE hkLoadLibraryExW(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags)
{
	if (wcsstr(lpLibFileName, L"easyanticheat_x64.dll"))
		return g_hMod;

	return oLoadLibraryExW(lpLibFileName, hFile, dwFlags);
}

LPVOID hkGetProcAddress(HMODULE hModule, LPCSTR lpProcName)
{
	if (strstr(lpProcName, "CreateGameClient"))
		return CreateGameClient;

	return oGetProcAddress(hModule, lpProcName);
}

BOOLEAN WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason != DLL_PROCESS_ATTACH)
		return TRUE;
	
	g_hMod = hModule;
	HMODULE hKERNEL32 = GetModuleHandleA("KERNEL32.DLL");

	oLoadLibraryExW = (fnLoadLibraryExW)GetProcAddress(hKERNEL32, "LoadLibraryExW");
	oGetProcAddress = (fnGetProcAddress)GetProcAddress(hKERNEL32, "GetProcAddress");

	Utils_HookImport("enlisted.exe", "KERNEL32.DLL", "LoadLibraryExW", hkLoadLibraryExW);
	Utils_HookImport("enlisted.exe", "KERNEL32.DLL", "GetProcAddress", hkGetProcAddress);

	return TRUE;
}
