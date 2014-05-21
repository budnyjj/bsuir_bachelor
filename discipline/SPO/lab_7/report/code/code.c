/* main.c */
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

/* complex.c */
#include "complex.h"
#include "io.h"

#include <stdio.h>

struct Complex
add(struct Complex c1, struct Complex c2) {
    struct Complex result;
    result.re = c1.re + c2.re;
    result.im = c1.im + c2.im;
    return result;
}

struct Complex
sub(struct Complex from, struct Complex to) {
    struct Complex result;
    result.re = from.re - to.re;
    result.im = from.im - to.im;
    return result;
}

struct Complex
mul(struct Complex c1, struct Complex c2) {
    struct Complex result;
    result.re = c1.re * c2.re - c1.im * c2.im;
    result.im = c1.re * c2.im + c1.im * c2.re;
    return result;
}

struct Complex
division(struct Complex from, struct Complex to, int * error) {
    struct Complex result;

    if (!(to.im) && !(to.re)) {
        printf("Invalid operation (devide by zero error)!\n");
        *error = 1;
    }

    result.re = (from.re * to.re + from.im * to.im) / (to.re * to.re + to.im * to.im);
    result.im = (from.re * to.im - from.im * to.re) / (to.re * to.re + to.im * to.im);
    return result;
}

/* complexes.h */
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

/* complex.h */
#ifndef __COMPLEX__
#define __COMPLEX__

struct Complex {
    double re;
    double im;
};

struct Complex add(struct Complex c1, struct Complex c2);
struct Complex sub(struct Complex c1, struct Complex c2);
struct Complex mul(struct Complex c1, struct Complex c2);
struct Complex division(struct Complex c1, struct Complex c2, int * error);

void writeComplex(char *fname, struct Complex *complex, int count);
int readComplex(char *fname, struct Complex *complex, int count);

#endif

/* complex_io.c */
#include "complex_io.h"
#include "complex.h"
#include "io.h"

#include <math.h>

#include <stdio.h>

#define PI 3.14159265358979323846

struct Complex
input_complex() {
    struct Complex complex;

    printf("Enter real part: ");
    while (!scanf("%lf", &complex.re)) {
        clear_input();
        printf("Input error! Try again: ");
    }

    printf("Enter imaginary part: ");

    while (!scanf("%lf", &complex.im)) {
        clear_input();
        printf("Input error! Try again: ");
    }

    return complex;
}

static struct Complex
change_complex_form(struct Complex complex, int * error) {
    struct Complex result;

    result.re = sqrt(complex.re * complex.re + complex.im * complex.im);

    if (complex.re > 0) {
        result.im = atan(complex.im / complex.re);
    } else if ((complex.re < 0) && (complex.im >= 0)) {
        result.im = atan(complex.im / complex.re) + PI;
    } else if ((complex.re < 0) && (complex.im < 0)) {
        result.im = atan(complex.im / complex.re) - PI;
    } else if ((!complex.re) && (complex.im > 0)) {
        result.im = PI / 2;
    } else if ((!complex.re) && (complex.im < 0)) {
        result.im = -(PI / 2);
    } else if ((!complex.re) && (!complex.im)) {
        *error = 1;
    }

    result.im *= 180 / PI;

    return result;
}

void
print_algebraic_form(struct Complex complex) {
    char sign = '+';
    if (complex.im < 0) {
        sign = '-';
        complex.im = -complex.im;
    }

    printf("%g %c %g*i\n", complex.re, sign, complex.im);
}

void
print_polar_form(struct Complex c) {
	int error = 0;
    struct Complex polar_complex;
    polar_complex = change_complex_form(c, &error);

    if (!error)
        printf("%g * e^(%g*i)\n", polar_complex.re, polar_complex.im);
    else
        printf("Indeterminate polar value!\n");
}

void
print_complex(struct Complex c) {
    printf("+-------------------------------------+\n");
    printf("Result (in algebraic form): ");
    print_algebraic_form(c);
    printf("Result (in polar form): ");
    print_polar_form(c);
    printf("+-------------------------------------+\n");
    wait_user_reaction();
}


void
print_complex_array(struct Complex *complex, int count) {
    int i;
	printf("\n");
    if (count > 0) {
        for (i = 0; i < count; i++) {
            printf("       a[%d]: ", i);
            print_algebraic_form(complex[i]);
        }
    }
    else {
        printf("   *** complex array is empty ***   \n");
    }
    printf("\n");
}

/* complex_io.h */
#ifndef __COMPLEX_IO__
#define __COMPLEX_IO__

struct Complex input_complex();

void print_algebraic_form(struct Complex complex);
void print_polar_form(struct Complex c);
void print_complex(struct Complex complex);
void print_complex_array(struct Complex *complex, int count);

#endif

/* io.c */
#include "io.h"
#include "complex.h"

#include <stdio.h>
#include <windows.h>

void
writeComplex(char *fname, struct Complex *complex, int count) {
    HANDLE hFile;
	BOOL isWritten = FALSE;
    DWORD dwBytesToWrite = sizeof(complex[0]) * count;
    DWORD dwBytesWritten = 0;
    hFile = CreateFileA ((LPCSTR)fname,         // the name of the file to be created or opened
                        GENERIC_WRITE,          // open for writing
                        0,                      // do not share
                        NULL,                   // default security
                        CREATE_ALWAYS,          // create a new, or open an existing file
                        FILE_ATTRIBUTE_NORMAL,  // normal file
                        NULL);                  // no attributes template

    if (hFile == INVALID_HANDLE_VALUE) {
        print_rw_message("Error! Cannot open file");
        return;
    }

    isWritten = WriteFile (hFile,              // open file handle
                           complex,            // start of data to write
                           dwBytesToWrite,     // number of bytes to write
                           &dwBytesWritten,    // number of bytes that were written
                           NULL);              // no overlapped structure

    if (isWritten == FALSE) {
        print_rw_message("Unable to write to file!");
    } else {
        if (dwBytesToWrite != dwBytesWritten) {
            print_rw_message("Not all of the bytes have been written!");
        } else {
            print_rw_message("Writing data is completed successfully!");
        }
    }
    CloseHandle(hFile);
}

int
readComplex(char *fname, struct Complex *complex, int count) {
    HANDLE hFile;
    BOOL isRead = FALSE;
    DWORD readBytes = 0;
    LPDWORD lpReadBytes = &readBytes;
    DWORD bytesToRead = sizeof(complex[0]) * count;

    hFile = CreateFileA (fname,                 // the name of the file to be opened
                        GENERIC_READ,           // open for reading
                        0,                      // do not share
                        NULL,                   // default security
                        OPEN_EXISTING,          // open only an existing file
                        FILE_ATTRIBUTE_NORMAL,  // normal file
                        NULL);                  // no attributes template

    if (hFile == INVALID_HANDLE_VALUE) {
        print_rw_message("Error! Cannot open file!");
        return 0;
    }

    isRead = ReadFile(hFile,                // open file handle
                      complex,              // buffer to write bytes
                      bytesToRead,          // number of bytes to read
                      lpReadBytes,          // number of bytes read
                      NULL);                // addres to OVERLAPPED structure

    if (isRead == FALSE) {
        print_rw_message("Unable to read data from file!");
        CloseHandle(hFile);
        return 0;
    }

    if (readBytes == bytesToRead) {
        print_rw_message("Data read successfully!");
        CloseHandle(hFile);
        return count;

    } else {
        print_rw_message("There is no such number of elements!");
        CloseHandle(hFile);
        return (readBytes / sizeof(complex[0]));
    }

    CloseHandle(hFile);
    return 0;
}

/* file_io.h */
#ifndef __FILE_IO__
#define __FILE_IO__

void writeComplex(char *fname, struct Complex *complex, int count);
int readComplex(char *fname, struct Complex *complex, int count);

#endif

/* filling_complexes.c */
#include "filling_complexes.h"
#include "complexes.h"
#include "complex_io.h"

#include <Windows.h>
#include <stdio.h>

void filling_complexes(struct Complexes *complexes, HANDLE hThread) {
	while (1) {
		printf("--> Second thread suspended\n");
		SuspendThread(hThread);

		printf("Press q to exit, or any key to continue...\n");
		char ch;
		ch = getchar();
		if (ch == 'q' || ch == 'Q') {
			return;
		}

		if (complexes->count == 0) {
			printf("Count of complex numbers to input: %i\n",
				complexes->complexes_size);
			while (complexes->count < complexes->complexes_size) {
				complexes->complexes[complexes->count] = input_complex();
				complexes->count++;
			}

			ResumeThread(hThread);
			printf("--> Second thread resumed\n");
			Sleep(100);
		}
	}
}

/* filling_complexes.h */
#ifndef __FILLING_COMPLEXES__
#define __FILLING_COMPLEXES__

#include <Windows.h>

void filling_complexes(struct Complexes *complexes, HANDLE hThread);

#endif

/* io.c */
#include "io.h"
#include <stdio.h>

static struct Complex change_complex_form(struct Complex complex);

void
clear_input() { while(getchar() != '\n'); }

void
wait_user_reaction() {
    printf("Press any key to continue...\n");
    clear_input();
}

void
print_rw_message(char *operation_result) {
    printf("---------------------------------------\n ");
    printf(operation_result);
    printf("\n---------------------------------------\n");
    wait_user_reaction();
}

/* io.h */
#ifndef __IO__
#define __IO__

void clear_input();
void wait_user_reaction();

void print_rw_message(char *operation_result);

#endif

/* write_complex_thread.c */
#include "write_complex_thread.h"
#include "complexes.h"
#include "file_io.h"

#include <Windows.h>
#include <stdio.h>

#define FILENAME "file.complex"

DWORD WINAPI writeComplexThread(struct Complexes *complexes) {
	while (1) {
		if (complexes->count == complexes->complexes_size) {
			writeComplex(FILENAME, complexes->complexes, complexes->count);
			complexes->count = 0;
		}
	}
	return 0;
}#ifndef __WRITE_COMPLEX_THREAD__
#define __WRITE_COMPLEX_THREAD__

/* write_complex_thread.h */
#include <Windows.h>

DWORD WINAPI writeComplexThread(struct Complexes *complexes);

#endif
