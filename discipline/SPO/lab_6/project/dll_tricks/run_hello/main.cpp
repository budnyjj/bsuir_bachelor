#undef UNICODE

#include <hello.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

typedef void* (*hello_p) ();
typedef void (*print_hello_p) ();

int main() {
	HINSTANCE h_dll = LoadLibrary("hello.dll");
	if (h_dll == NULL) {
		printf("Failed to load library");	
	} else {
		hello_p hello = (hello_p) GetProcAddress(h_dll, "hello");
		print_hello_p print_hello = (print_hello_p) hello();
		print_hello();
		FreeLibrary(h_dll);
	}

	getchar();
	return 0;
}