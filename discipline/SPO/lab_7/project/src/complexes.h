#ifndef __COMPLEXES__
#define __COMPLEXES__

#include "complex.h"

#define COMPLEXES_SIZE 5

struct Complexes {
	int count;
	int complexes_size;
	struct Complex complexes[COMPLEXES_SIZE];
};

#endif