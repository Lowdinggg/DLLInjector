#include <iostream>
#include "DLLInjector.h"

BOOL injectIntoProcess(int processId, char* dllPath) {
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, processId);
	if(!pHandle) {
		printf("Could not process \n");
		return FALSE;
	}
	DWORD LoadLibAdr = GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryA");
	if(!LoadLibAdr) {
		printf("Could not get LoadLibraryA address \n");
		return FALSE;
	}
	LPVOID dllPathAddressInRemoteMemory = VirtualAllocEx(pHandle, NULL, sizeof(dllPath), MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	WriteProcessMemory(pHandle, dllPathAddressInRemoteMemory, dllPath, sizeof(dllPath), 0);
	HANDLE remoteThread = CreateRemoteThread(pHandle, NULL, NULL, (LPTHREAD_START_ROUTINE) LoadLibAdr, dllPathAddressInRemoteMemory, NULL, NULL);
	if(!remoteThread) {
		printf("Creating remote thread failed \n" );
		return FALSE;
	}
	WaitForSingleObject(remoteThread, INT_MAX);
	VirtualFreeEx(pHandle, dllPathAddressInRemoteMemory, sizeof(dllPath), MEM_FREE);
	return TRUE;
}
