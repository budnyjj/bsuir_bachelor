#include "write_complex_thread.h"
#include "complexes.h"
#include "file_io.h"

#include <windows.h>
#include <stdio.h>

#define FILENAME "complex"

DWORD WINAPI writeComplexThread(struct Complexes *complexes) {
	DWORD wait_result;
	BOOL b_continue = TRUE;

	while (b_continue) {
		wait_result = WaitForSingleObject(complexes->semaphore, 0L);
		switch (wait_result) {
		case WAIT_OBJECT_0:
			{
				char* filename = FILENAME;
				//sprintf(filename, "%s_%d.data", FILENAME, GetCurrentThreadId());
				b_continue = FALSE;
				writeComplex(filename, complexes->complexes, complexes->count);

				Sleep(5000);
				
				if (!ReleaseSemaphore(complexes->semaphore, 1, NULL))
					printf("Cannot release semaphore: %d\n", GetLastError());
				break;
			}
		case WAIT_TIMEOUT:
			printf("Thread %d: wait timeout\n", GetCurrentThreadId());
			break;
		}
	}

	return 0;
}