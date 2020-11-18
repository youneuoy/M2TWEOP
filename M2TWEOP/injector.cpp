#include "injector.h"
#include <TlHelp32.h>



void injector::start()
{
   // test();
	threadF();

}

void injector::threadF()
{

	//string libP = Startup::gameInfo.realDir;
	string libP = Startup::gameInfo.currentMod;
	libP = libP + "\\youneuoy_Data\\plugins\\HotSeatToolLib.dll";


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

	SIZE_T numW;
	WriteProcessMemory(hMTW2, pDllPath, (LPVOID)libP.c_str(), SizePatch, &numW);
	if(!numW)return;
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
/*void injector::threadF()
{
	ofstream f1("test.log");
	f1 << "start"<<endl;
	//LPCSTR Dll = "E:\\Games\\Steam\\steamapps\\common\\Medieval II Total War\\mods\\BellumCrucis7_hotseat\\HotSeatToolLib.dll";
	string libP= Startup::gameInfo.currentMod;
	libP = libP + "\\HotSeatToolLib.dll";
	LPCSTR Dll = libP.c_str();

	DWORD ProcessId = 0;
	f1 << "search:" << endl;
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
	loaderdata LoaderParams;
	f1 << "done" << endl;
	HANDLE hFile = CreateFileA(Dll, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
		OPEN_EXISTING, 0, NULL); // Open the DLL

	DWORD FileSize = GetFileSize(hFile, NULL);
	PVOID FileBuffer = VirtualAlloc(NULL, FileSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	f1 << "read:" << endl;
	// Read the DLL
	DWORD read;
	ReadFile(hFile, FileBuffer, FileSize, &read, NULL);
	f1 << "done" << endl;
	// Target Dll's DOS Header
	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)FileBuffer;
	// Target Dll's NT Headers
	PIMAGE_NT_HEADERS pNtHeaders = (PIMAGE_NT_HEADERS)((LPBYTE)FileBuffer + pDosHeader->e_lfanew);
	f1 << "done2" << endl;
	// Opening target process.
	HANDLE hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION |
		PROCESS_VM_WRITE| PROCESS_QUERY_INFORMATION, FALSE, ProcessId);
	// Allocating memory for the DLL
	PVOID ExecutableImage = VirtualAllocEx(hProcess, NULL, pNtHeaders->OptionalHeader.SizeOfImage,
		MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	f1 << "opened" << endl;
	// Copy the headers to target process
	WriteProcessMemory(hProcess, ExecutableImage, FileBuffer,
		pNtHeaders->OptionalHeader.SizeOfHeaders, &read);

	// Target Dll's Section Header
	PIMAGE_SECTION_HEADER pSectHeader = (PIMAGE_SECTION_HEADER)(pNtHeaders + 1);
	// Copying sections of the dll to the target process
	for (int i = 0; i < pNtHeaders->FileHeader.NumberOfSections; i++)
	{
		WriteProcessMemory(hProcess, (PVOID)((LPBYTE)ExecutableImage + pSectHeader[i].VirtualAddress),
			(PVOID)((LPBYTE)FileBuffer + pSectHeader[i].PointerToRawData), pSectHeader[i].SizeOfRawData, &read);
	}

	// Allocating memory for the loader code.
	PVOID LoaderMemory = VirtualAllocEx(hProcess, NULL, 4096, MEM_COMMIT | MEM_RESERVE,
		PAGE_EXECUTE_READWRITE); // Allocate memory for the loader code

	LoaderParams.ImageBase = ExecutableImage;
	LoaderParams.NtHeaders = (PIMAGE_NT_HEADERS)((LPBYTE)ExecutableImage + pDosHeader->e_lfanew);

	LoaderParams.BaseReloc = (PIMAGE_BASE_RELOCATION)((LPBYTE)ExecutableImage
		+ pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);
	LoaderParams.ImportDirectory = (PIMAGE_IMPORT_DESCRIPTOR)((LPBYTE)ExecutableImage
		+ pNtHeaders->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);

	LoaderParams.fnLoadLibraryA = LoadLibraryA;
	LoaderParams.fnGetProcAddress = GetProcAddress;
	f1 << "allocated" << endl;
	// Write the loader information to target process
	WriteProcessMemory(hProcess, LoaderMemory, &LoaderParams, sizeof(loaderdata),
		 &read);
	// Write the loader code to target process
	WriteProcessMemory(hProcess, (PVOID)((loaderdata*)LoaderMemory + 1), LibraryLoader,
		(DWORD)stub - (DWORD)LibraryLoader, &read);
	// Create a remote thread to execute the loader code


	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)((loaderdata*)LoaderMemory + 1),
		LoaderMemory, 0, NULL);
	if (hThread == NULL)
	{
		DWORD err=GetLastError();
		string s = to_string(err);
		MessageBoxA(NULL, "Something goes wrong!", s.c_str(), NULL);
	}
	f1 << "loaded" << endl;
	f1 << "Loader: " << std::hex << LoaderMemory << std::endl;
	f1 << "Memory: " << std::hex << ExecutableImage << std::endl;
	// Wait for the loader to finish executing
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	std::cin.get();
	// free the allocated loader code
	VirtualFreeEx(hProcess, LoaderMemory, 0, MEM_RELEASE);
	CloseHandle(hProcess);
	f1 << "all!" << endl;
	f1.close();
	if (Startup::cfg.closeAfterStart==true)
		exit(0);
}
*/