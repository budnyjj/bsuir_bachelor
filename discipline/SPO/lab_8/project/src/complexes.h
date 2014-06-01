#ifndef __COMPLEXES__
#define __COMPLEXES__

#include "complex.h"
#include "windows.h"

struct Complexes {
	HANDLE semaphore;
	int count;
	struct Complex* complexes;
};

#endif