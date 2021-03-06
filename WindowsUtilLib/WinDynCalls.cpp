#include <stdio.h>
#include "WinDynCalls.h"
KERNEL32_API_LIST(API_DLR)


//Only load dll located in SystemDirectory e.g C:\Windows\System32
HMODULE SafeLoadLibrary(const WCHAR* dllName) {
	WCHAR dllAbsPath[MAX_PATH]{};
	UINT res = GetSystemDirectoryW(dllAbsPath, dimof1(dllAbsPath));
	if (!res||res>=dimof1(dllAbsPath))
		return nullptr;
	res = PathCchAppend(dllAbsPath, dimof1(dllAbsPath), dllName);
	if (res != S_OK)
		return nullptr;
	return LoadLibraryW(dllAbsPath);
}
void InitDynCalls() {
	HMODULE h = SafeLoadLibrary(L"kernel32.dll");
	if (h == NULL)
		CrashMe();
	KERNEL32_API_LIST(API_LOAD);

}
