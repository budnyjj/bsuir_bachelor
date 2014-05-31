#include "filling_complexes.h"
#include "complexes.h"
#include "complex_io.h"
#include "complex.h"
#include "io.h"
#include "write_complex_thread.h"

#include <windows.h>
#include <stdio.h>
#include <malloc.h>

#define MAX_SEM_COUNT 1
#define MAX_THREAD_COUNT 1

static void get_number_complexes(int* num_complexes);
static void create_writer(struct Complexes* complexes);

void filling_complexes() {
	HANDLE semaphore = CreateSemaphore(NULL, MAX_SEM_COUNT, MAX_SEM_COUNT, NULL);
	if (semaphore == NULL) {
		printf("Cannot create semaphore! Aborting...");
		return;
	}

	while (1) {
		char ch;
		int i;
		struct Complexes* complexes = NULL;

		printf("Press q to exit, or any key to enter numbers...\n");
		ch = getchar();
		clear_input();
		if (ch == 'q' || ch == 'Q') {
			return;
		}
		
		complexes = (struct Complexes *) calloc(1, sizeof(struct Complexes));
		if (complexes == NULL) {
			printf("Cannot allocate memory for complexes!\n");
			continue;
		}

		get_number_complexes(&(complexes->count));
		complexes->complexes = (struct Complex *) malloc((complexes->count) * sizeof(struct Complex));
		if (complexes->complexes == NULL) {
			printf("Cannot allocate memory for requested number of complex numbers!\n");
			free(complexes);
			continue;
		}

		for (i = 0; i < (complexes->count); i++) {
			printf("\nInput complex number no. %i:\n", i+1);
			input_complex(&(complexes->complexes[i]));
		}
		complexes->semaphore = semaphore;
		create_writer(complexes);
	}

	WaitForSingleObject(semaphore, 0L);
	CloseHandle(semaphore);
}

static void get_number_complexes(int* num_complexes) {
	while (1) {
		printf("Input number of complexes: ");
		scanf("%i", num_complexes);
		clear_input();
		if (*num_complexes > 0) {
			return;
		}
		else {
			printf("Number of complexes must be greater than zero!\n");
		}
	}
}

static void create_writer(struct Complexes* complexes) {
	HANDLE hThread;
	DWORD ThreadId;
	hThread = CreateThread(NULL, 0, 
						   (LPTHREAD_START_ROUTINE) writeComplexThread,
						   complexes, 0, &ThreadId);
	if (hThread == NULL) {
		printf("Cannot create thread!");
		free(&(complexes->complexes));
		free(complexes);
	}
//	Sleep(100);
}