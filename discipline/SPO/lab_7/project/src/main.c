#include "write_complex_thread.h"
#include "filling_complexes.h"
#include "complexes.h"

#include <Windows.h>
#include <stdio.h>

int main() {
	HANDLE hThread;
	DWORD ThreadId;
	LPTHREAD_START_ROUTINE function = writeComplexThread;
	struct Complexes complexes;
	complexes.complexes_size = COMPLEXES_SIZE;
	complexes.count = 0;

	hThread = CreateThread(NULL, 0, function, &complexes, 0, &ThreadId);

	filling_complexes(&complexes, hThread);
	
	CloseHandle(hThread);
	return 0;
}