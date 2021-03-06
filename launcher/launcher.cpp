#include "resource.h"
#define WIN32_LEAN_AND_MEAN
#include <sdkddkver.h>
#include <Windows.h>

#ifdef _CONSOLE
int wmain(void)
#else
int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
#endif
{
	wchar_t str[2048];
	LoadString(GetModuleHandle(nullptr), IDS_STRING101, str, sizeof(str) / sizeof(str[0]));
	if (!str) {
		return -1;
	}
	STARTUPINFO si = { 0 };
	si.cb = sizeof(STARTUPINFO);
	PROCESS_INFORMATION pi;
	auto cl = GetCommandLine();
	if (!CreateProcess(str, cl, nullptr, nullptr, TRUE, CREATE_UNICODE_ENVIRONMENT, nullptr, nullptr, &si, &pi)) {
		return -2;
	}
	DWORD exitCode = 0;
#ifdef _CONSOLE
	WaitForSingleObject(pi.hProcess, INFINITE);
	GetExitCodeProcess(pi.hProcess, &exitCode);
#endif
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
    return (int)exitCode;
}
