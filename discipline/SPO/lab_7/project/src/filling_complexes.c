#include "filling_complexes.h"
#include "complexes.h"
#include "complex_io.h"

#include <Windows.h>
#include <stdio.h>

void filling_complexes(struct Complexes *complexes, HANDLE hThread) {
	while (1) {
		printf("Press q to exit, or any key to continue...\n");
		char ch;
		ch = getchar();
		if (ch == 'q' || ch == 'Q') {
			return;
		}
		
		if (complexes->count == 0) {
			SuspendThread(hThread);

			printf("Count of complex numbers to input: %i\n",
				complexes->complexes_size);
			while (complexes->count < complexes->complexes_size) {
				complexes->complexes[complexes->count] = input_complex();
				complexes->count++;
			}
			
			ResumeThread(hThread);
			Sleep(100);
		}
	}
}