#include "injector.h"


void injector::start()
{
	threadF();
}

void injector::threadF()
{
	//string libP = Startup::gameInfo.realDir;
	string libP = Startup::gameInfo.currentMod;
	libP = libP + "\\HotSeatToolLib.dll";

	HANDLE hMTW2;

	DWORD ProcessId = 0;

	HWND hWnd = 0;
	UINT32 stop = 0;
	do {
		stop++;
		Sleep(100);
		hWnd = FindWindowA(0, ("Medieval 2"));
		if (stop == 500)
			exit(0);
	} while (hWnd == 0);
	GetWindowThreadProcessId(hWnd, &ProcessId);

	hMTW2 = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION |
		PROCESS_QUERY_LIMITED_INFORMATION | PROCESS_VM_OPERATION |
		PROCESS_VM_WRITE | PROCESS_VM_READ
		, 0, ProcessId);

	size_t SizePatch = libP.size();
	LPVOID pDllPath = VirtualAllocEx(hMTW2, NULL, SizePatch, MEM_COMMIT, PAGE_READWRITE);
	if (!pDllPath)return;

	SIZE_T numW=0;
	WriteProcessMemory(hMTW2, pDllPath, (LPVOID)libP.c_str(), SizePatch, &numW);
	if (!numW)return;
	HMODULE kernel = GetModuleHandleA("Kernel32.dll");
	if (!kernel)return;
	DWORD Adr = (DWORD)GetProcAddress(kernel, "LoadLibraryA");
	if (!Adr)return;
	HANDLE hThread = CreateRemoteThread(hMTW2, 0, 0, (LPTHREAD_START_ROUTINE)Adr, pDllPath, 0, 0);
	if (!hThread)return;
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	VirtualFreeEx(hMTW2, pDllPath, 0, MEM_RELEASE);

	CloseHandle(hMTW2);
}