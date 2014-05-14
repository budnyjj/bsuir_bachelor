#include "write_complex_thread.h"
#include "filling_complexes.h"
#include "complexes.h"

#include <Windows.h>
#include <stdio.h>

int main() {
	printf("-> Main thread created\n");
	HANDLE hThread;
	DWORD ThreadId;
	LPTHREAD_START_ROUTINE function = writeComplexThread;
	struct Complexes complexes;
	complexes.complexes_size = COMPLEXES_SIZE;
	complexes.count = 0;

	hThread = CreateThread(NULL, 0, function, &complexes, 0, &ThreadId);
	printf("--> Second thread created\n");

	filling_complexes(&complexes, hThread);
	
	CloseHandle(hThread);
	printf("--> Second thread closed\n");

	printf("-> Main thread closed\n");
	printf("Press any key to exit...");
	getch();
	return 0;
}