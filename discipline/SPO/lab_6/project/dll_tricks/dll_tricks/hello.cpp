#include "hello.h"
#include "stdafx.h"
#include <stdio.h>

static void print_hello() {
	printf("%s", "Hello, world!");
}

void * hello() {
	return print_hello;
}