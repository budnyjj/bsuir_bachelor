#include "write_complex_thread.h"
#include "complexes.h"
#include "file_io.h"

#include <Windows.h>

#define FILENAME "file.complex"

DWORD WINAPI writeComplexThread(struct Complexes *complexes) {
	while (1) {
		if (complexes->count == complexes->complexes_size) {
			writeComplex(FILENAME, complexes->complexes, complexes->count);
			complexes->count = 0;
		}
	}
	return 0;
}