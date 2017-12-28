// DLLInjector.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "DLLInjector.h"


int main(int argc, char* argv[]) {
	if(argc < 3) {
		printf("Usage: injectDll <process> <DLL Path>");
		return -1;
	}
	int processName = atoi(argv[1]);
	printf(processName); printf("\n");
	char* dllPath = argv[2];
	injectIntoProcess(processName, dllPath);
	return 0;
}

