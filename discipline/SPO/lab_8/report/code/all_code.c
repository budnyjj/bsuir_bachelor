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


/* complex.c */
/* complexes.c */ 

#include "complexes.h"
#include "complex.h"

/* complexes.c */
/* complex_io.c */ 

#include "complex_io.h"
#include "complex.h"
#include "io.h"

#include <math.h>

#include <stdio.h>

#define PI 3.14159265358979323846

int
input_complex(struct Complex* complex) {
    printf("Enter real part: ");
    while (!scanf("%lf", &(complex->re))) {
        clear_input();
        printf("Input error! Try again: ");
    }
	clear_input();
    printf("Enter imaginary part: ");
    
    while (!scanf("%lf", &(complex->im))) {
        clear_input();
        printf("Input error! Try again: ");
    }
    clear_input();
    return 0;
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



/* complex_io.c */
/* file_io.c */ 

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
    hFile = CreateFileA ((LPCSTR)fname,
                        FILE_APPEND_DATA,
                        0,
                        NULL,
                        OPEN_EXISTING,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL);

    if (hFile == INVALID_HANDLE_VALUE) {        
        print_rw_message("Error! Cannot open file");
        return;
    }
    
    isWritten = WriteFile (hFile,
                           complex,
                           dwBytesToWrite,
                           &dwBytesWritten,
                           NULL);

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

    hFile = CreateFileA (fname,
                        GENERIC_READ,
                        0,
                        NULL,
                        OPEN_EXISTING,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL);

    if (hFile == INVALID_HANDLE_VALUE) {
        print_rw_message("Error! Cannot open file!");
        return 0;
    }

    isRead = ReadFile(hFile,
                      complex,
                      bytesToRead,
                      lpReadBytes,
                      NULL);

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

/* file_io.c */
/* filling_complexes.c */ 

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

/* filling_complexes.c */
/* io.c */ 

#include "io.h"

#include <stdio.h>

static struct Complex change_complex_form(struct Complex complex);

void
clear_input() { while(getchar() != '\n'); }

void
wait_user_reaction() {
    printf("Press any key to continue...\n");
}

void 
print_rw_message(char *operation_result) {
    printf("---------------------------------------\n ");
    printf(operation_result);
    printf("\n---------------------------------------\n");
    wait_user_reaction();
}

/* io.c */
/* main.c */ 

#include "filling_complexes.h"

#include <stdio.h>

int main() {
	filling_complexes();
	getchar();
	return 0;
}

/* main.c */
/* write_complex_thread.c */ 

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
                free(complexes->complexes);
                free(complexes);

				break;
			}
		case WAIT_TIMEOUT:
			printf("Thread %d: wait timeout\n", GetCurrentThreadId());
			break;
		}
	}

	return 0;
}

/* write_complex_thread.c */
/* complexes.h */ 

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

/* complexes.h */
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

/* complex.h */
/* complex_io.h */ 

#ifndef __COMPLEX_IO__
#define __COMPLEX_IO__

int input_complex(struct Complex*);

void print_algebraic_form(struct Complex complex);
void print_polar_form(struct Complex c);

void print_complex(struct Complex complex);
void print_complex_array(struct Complex *complex, int count);


#endif

/* complex_io.h */
/* file_io.h */ 

#ifndef __FILE_IO__
#define __FILE_IO__

void writeComplex(char *fname, struct Complex *complex, int count);
int readComplex(char *fname, struct Complex *complex, int count);

#endif

/* file_io.h */
/* filling_complexes.h */ 

#ifndef __FILLING_COMPLEXES__
#define __FILLING_COMPLEXES__

void filling_complexes();

#endif

/* filling_complexes.h */
/* io.h */ 

#ifndef __IO__
#define __IO__

void clear_input();
void wait_user_reaction();

void print_rw_message(char *operation_result);

#endif

/* io.h */
/* write_complex_thread.h */ 

#ifndef __WRITE_COMPLEX_THREAD__
#define __WRITE_COMPLEX_THREAD__

#include <Windows.h>

DWORD WINAPI writeComplexThread(struct Complexes *complexes);

#endif

/* write_complex_thread.h */
