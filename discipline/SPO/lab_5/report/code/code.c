/* main.c */

#include "io.h"
#include "complex.h"
#include "interface.h"

#include "stdio.h"
#include "stdlib.h"

#define COMPLEX_SIZE_DEFAULT 2

#define COMPLEX1_RE 1
#define COMPLEX1_IM 2.2
#define COMPLEX2_RE -5
#define COMPLEX2_IM 3

int main() {
    struct Complex *complex = (struct Complex *) calloc(COMPLEX_SIZE_DEFAULT, sizeof(struct Complex));
    int size = COMPLEX_SIZE_DEFAULT;
    int count_of_elements = COMPLEX_SIZE_DEFAULT;

    struct Complex c1, c2, result;

    complex[0].re = COMPLEX1_RE;
    complex[0].im = COMPLEX1_IM;
    complex[1].re = COMPLEX2_RE;
    complex[1].im = COMPLEX2_IM;

    c1.re = COMPLEX1_RE;
    c1.im = COMPLEX1_IM;
    c2.re = COMPLEX2_RE;
    c2.im = COMPLEX2_IM;

    while (1) {
        print_main_menu(c1, c2);
        char ch = getchar();
        clear_input();
        switch (ch) {
        case '1':
        {
            int index = 0;
            change_complex_interface(&c1, complex, count_of_elements);
            break;
        }
        case '2':
        {
            int index = 1;
            change_complex_interface(&c2, complex, count_of_elements);
            break;
        }
        case 'a':
        case 'A':
            result = add(c1, c2);
            print_complex(result);
            break;
        case 's':
        case 'S':
            result = sub(c1, c2);
            print_complex(result);
            break;
        case 'm':
        case 'M':
            result = mul(c1, c2);
            print_complex(result);
            break;
        case 'd':
        case 'D':
            result = division(c1, c2);
            if (!result.error) {
                print_complex(result);
            }
            break;
        case 'r':
        case 'R':
            complex = read_file_interface(complex, &size, &count_of_elements);
            break;
        case 'w':
        case 'W':
            complex = write_file_interface(complex, &size, &count_of_elements);
            break;
        case 'q':
        case 'Q':
            return 0;
        default:
            printf("Incorrect input, please choose an existing element\n");
        }
    }
    return 0;
}

/* interface.h */

#ifndef __INTERFACE__
#define __INTERFACE__

struct Complex * write_file_interface(struct Complex *complex, int *size, int *count_of_elements);
struct Complex * read_file_interface(struct Complex *complex, int *size, int *count_of_elements);

void change_complex_interface(struct Complex *c, struct Complex *source_array, int size);

#endif

/* interface.c */

#include "interface.h"
#include "complex.h"
#include "file_io.h"
#include "io.h"

#include "stdlib.h"
#include "stdio.h"

#define INPUT_SOURCE "file.complex"
#define OUTPUT_SOURCE "file.complex"

#define COUNT_ELEMENTS_TO_WRITE_DEFAULT 2
#define COUNT_ELEMENTS_TO_READ_DEFAULT 50
#define COUNT_ELEMENTS_TO_READ_MAX 100000

static int get_index_to_edit_complex(int count_of_elements);
static int get_count_of_elements_to_rw(int count_of_elements);
static int get_new_count_to_read();
static int realloc_complex(struct Complex **complex, int *size, double coeff);

struct Complex *
write_file_interface(struct Complex *complex, int *size, int *count_of_elements) {
    int count_elements_to_write = COUNT_ELEMENTS_TO_WRITE_DEFAULT;
    char file_source[] = OUTPUT_SOURCE;

    while (1) {
        print_write_file_menu(complex, *count_of_elements, count_elements_to_write, file_source);
        char choice = getchar();
        clear_input();
        switch (choice) {
        case 'c':
        case 'C':
            count_elements_to_write = get_count_of_elements_to_rw(*count_of_elements);
            break;
        case 'e':
        case 'E':
            if (*count_of_elements > 0) {
                int index = get_index_to_edit_complex(*count_of_elements);
                printf("Input new complex number\n");
                complex[index] = input_complex();
            }
            else {
                printf("No have items to change!\n");
                wait_user_reaction();
            }
            break;
        case 'a':
        case 'A':
        {
            int realloc_error = 0;
            if (*count_of_elements >= *size) {
                realloc_error = realloc_complex(&complex, size, 2.0);
            }
            if (!realloc_error) {
                printf("Please, input new complex number.\n");
                complex[(*count_of_elements)++] = input_complex();
            }
            else {
                printf("Impossible to add element. No have memory!\n");
                wait_user_reaction();
            }
            break;
        }
        case 'd':
        case 'D':
        {
            if (*count_of_elements > 0) {
                if (*count_of_elements <= ((*size) * 0.5)) {
                    realloc_complex(&complex, size, 0.5);
                }
                (*count_of_elements)--;
            }
            else {
                printf("Array of complex numbers is empty!\n");
                wait_user_reaction();
            }
            break;
        }
        case 'w':
        case 'W':
        {
            if (*count_of_elements >= count_elements_to_write) {
                writeComplex(file_source, complex, count_elements_to_write);
                return complex;
            }
            else {
                printf("Change count of elements to write!\n");
                wait_user_reaction();
                break;
            }
        }
        case 'b':
        case 'B':
            return complex;
        default:
            printf("Incorrect input, please choose an existing element\n");
        }
    }
}

struct Complex *
read_file_interface(struct Complex *complex, int *size, int *count_of_elements) {
    int count_elements_to_read = COUNT_ELEMENTS_TO_READ_DEFAULT;
    char file_source[] = INPUT_SOURCE;

    while (1) {
        print_read_file_menu(file_source, count_elements_to_read);
        char choice = getchar();
        clear_input();
        switch (choice) {
        case 'c':
        case 'C':
            count_elements_to_read = get_count_of_elements_to_rw(COUNT_ELEMENTS_TO_READ_MAX);
            break;
        case 'r':
        case 'R':
        {
            int realloc_error = 0;
            while (count_elements_to_read > *size) {
                realloc_error = realloc_complex(&complex, size, 2.0);
                if (realloc_error) {
                    return complex;
                }
            }

            if (!realloc_error) {
                int read_elements = 0;
                read_elements = readComplex(file_source, complex, count_elements_to_read);
                *count_of_elements = read_elements;

                if (read_elements) {
                    print_read_results(complex, read_elements);
                    while (read_elements <= ((*size)*0.5)) {
                        realloc_complex(&complex, size, 0.5);
                    }
                }

                return complex;
            }
            break;
        }
        case 'b':
        case 'B':
            return complex;
        default:
            printf("Incorrect input, please choose an existing element\n");
        }
    }
}

void
change_complex_interface(struct Complex *c, struct Complex *source_array, int count_of_elements) {
    while (1) {
        print_change_complex_menu();
        char choice = getchar();
        clear_input();
        switch (choice) {
        case 'e':
        case 'E':
            printf("Input new complex number.\n");
            *c = input_complex();
            return;
        case 'c':
        case 'C':
            if (count_of_elements > 0) {
            print_complex_array(source_array, count_of_elements);
            int index = get_index_to_edit_complex(count_of_elements);
            *c = source_array[index];
            }
            else {
                printf("No have existing items!\n");
                wait_user_reaction();
            }
            break;
        case 'b':
        case 'B':
            return;
        default:
            printf("Incorrect input, please choose an existing element\n");
        }
    }
}

static int
get_index_to_edit_complex(int count_of_elements) {
    int index = 0;
    printf("Choose some index:\n");
    while (!scanf("%d", &index) || (index < 0) || (index > count_of_elements - 1)) {
        printf("Input incorrect! Index interval: [0; %d]\n"
               "Please, try again: ", count_of_elements - 1);
        clear_input();
    }
    clear_input();
    return index;
}

static int
get_count_of_elements_to_rw(int count_of_elements) {
    int new_count = 0;
    printf("Input new count of elements: ");
    while (!scanf("%d", &new_count) || (new_count < 0) || (new_count > count_of_elements)) {
        printf("Input incorrect! Count interval: [0; %d]\n"
               "Please, try again: ", count_of_elements);
        clear_input();
    }
    clear_input();
    return new_count;
}

static int
realloc_complex(struct Complex **complex, int *size, double coeff) {
    struct Complex * new_complex = 0;
    new_complex = (struct Complex *) realloc(*complex, (int)(coeff * (*size) * sizeof(struct Complex)));

    if (new_complex) {
        (*size) = (int) ((*size) * coeff);
        *complex = new_complex;
        return 0;
    }
    else {
        printf("Realloc error!\n");
        wait_user_reaction();
        return 1;
    }
}

/* complex.h */

#ifndef __COMPLEX__
#define __COMPLEX__

struct Complex {
    double re;
    double im;
    int error; // error number
};

struct Complex add(struct Complex c1, struct Complex c2);
struct Complex sub(struct Complex c1, struct Complex c2);
struct Complex mul(struct Complex c1, struct Complex c2);
struct Complex division(struct Complex c1, struct Complex c2);

#endif

/* complex.c */

#include "complex.h"

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
division(struct Complex from, struct Complex to) {
    struct Complex result;
    result.error = 0;

    if (!(to.im) && !(to.re)) {
        printf("Invalid operation (devide by zero error)!\n");
        result.error = 1;
    }

    result.re = (from.re * to.re + from.im * to.im) / (to.re * to.re + to.im * to.im);
    result.im = (from.re * to.im - from.im * to.re) / (to.re * to.re + to.im * to.im);
    return result;
}

/* io.h */

#ifndef __IO__
#define __IO__

void clear_input();
void wait_user_reaction();

struct Complex input_complex();

void print_complex(struct Complex complex);
void print_complex_array(struct Complex *complex, int count);
void print_read_results(struct Complex *complex, int count);

void print_write_file_menu(struct Complex *complex, int count_all_elements, int count_elements_to_write, char *file_source);
void print_read_file_menu(char *file_source, int count_elements_to_read);

void print_main_menu(struct Complex c1, struct Complex c2);
void print_change_complex_menu();

void print_rw_message(char *operation_result);

#endif

/* io.c */

#include "io.h"
#include "complex.h"

#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

static struct Complex change_complex_form(struct Complex complex);

void
clear_input() { while(getchar() != '\n'); }

void
wait_user_reaction() {
    printf("Press any key to continue...\n");
    clear_input();
}

struct Complex
input_complex() {
    struct Complex complex;

    printf("Enter real part: ");
    while (!scanf("%lf", &complex.re)) {
        clear_input();
        printf("Input error! Try again: ");
    }
    clear_input();

    printf("Enter imaginary part: ");

    while (!scanf("%lf", &complex.im)) {
        clear_input();
        printf("Input error! Try again: ");
    }
    clear_input();

    return complex;
}

static struct Complex
change_complex_form(struct Complex complex) {
    struct Complex result;
    result.error = 0; // no error

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
        result.error = 1;
    }

    result.im *= 180 / PI;

    return result;
}

static void
print_algebraic_form(struct Complex complex) {
    char sign = '+';
    if (complex.im < 0) {
        sign = '-';
        complex.im = -complex.im;
    }

    printf("%g %c %g*i\n", complex.re, sign, complex.im);
}

static void
print_polar_form(struct Complex c) {
    struct Complex polar_complex;
    polar_complex = change_complex_form(c);

    if (!polar_complex.error)
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
print_main_menu(struct Complex c1, struct Complex c2) {
    printf(
           "\n+------------- Main menu -------------+\n"
           "|                                     |\n");
    printf("   first  complex number: "); print_algebraic_form(c1);
    printf("   second complex number: "); print_algebraic_form(c2);
    printf(
           "|                                     |\n"
           "+-------------------------------------+\n"
           "|  1 --- Edit  first complex number   |\n"
           "|  2 --- Edit second complex number   |\n"
           "|                                     |\n"
           "+--- Choose operation: ---------------+\n"
           "|  a --- Add complex numbers          |\n"
           "|  s --- Sub complex numbers          |\n"
           "|  m --- Mul complex numbers          |\n"
           "|  d --- Div complex numbers          |\n"
           "|                                     |\n"
           "+--- Read/Write file operations: -----|\n"
           "|  r --- Read from file               |\n"
           "|  w --- Write to file                |\n"
           "+  - - - - - - - - - - - - - - - - -  +\n"
           "|             q --- Quit              |\n"
           "+-------------------------------------+\n"
           "\nYour choice: "
           );
}

void
print_write_file_menu(struct Complex *complex, int count_of_all_elements, int count_elements_to_write, char *file_source) {
    printf(
           "\n+-------- Write to file menu  --------+\n"
           "|                                     |\n");
    printf("      File source: %s\n", file_source);

    print_complex_array(complex, count_of_all_elements);

    printf("      Count of numbers to write: %d\n", count_elements_to_write);

    printf(
           "|  c --- edit Count of write numbers  |\n"
           "|  - - - - - - - - - - - - - - - - -  |\n"
           "|  e --- Edit complex number          |\n"
           "|  a --- Add complex number           |\n"
           "|  d --- Delete complex number        |\n"
           "|  w --- Write complex number         |\n"
           "|  - - - - - - - - - - - - - - - - -  |\n"
           "|  b --- Back to main menu            |\n"
           "+-------------------------------------+\n"
           "\nYour choice: "
           );
}

void
print_read_file_menu(char *file_source, int count_elements_to_read) {
    printf("\n+------- Read from file menu  --------+\n\n");

    printf("        File source: %s\n", file_source);
    printf("     Count of numbers to read: %d\n", count_elements_to_read);

    printf(
         "\n|  c --- edit Count of read numbers   |\n"
           "|  r --- Read numbers from file       |\n"
           "|  - - - - - - - - - - - - - - - - -  |\n"
           "|  b --- Back to main menu            |\n"
           "+-------------------------------------+\n"
           "\nYour choice: "
           );
}

void
print_complex_array(struct Complex *complex, int count) {
    printf("\n");
    if (count > 0) {
        for (int i = 0; i < count; i++) {
            printf("       a[%d]: ", i);
            print_algebraic_form(complex[i]);
        }
    }
    else {
        printf("   *** complex array is empty ***   \n");
    }
    printf("\n");
}

void
print_read_results(struct Complex *complex, int count) {
    printf("------------- Read results ------------\n");
    printf("  Count of read elements: %d", count);
    print_complex_array(complex, count);
    printf("---------------------------------------\n");
    wait_user_reaction();
}

void
print_change_complex_menu() {
    printf(
        "+-------------------------------------+\n"
        "|  e --- Edit complex number          |\n"
        "|  c --- Choose an existing item      |\n"
        "|  - - - - - - - - - - - - - - - - -  |\n"
        "|  b --- Back to main menu            |\n"
        "+-------------------------------------+\n"
        "\nYour choice: "
        );
}

void
print_rw_message(char *operation_result) {
    printf("---------------------------------------\n ");
    printf(operation_result);
    printf("\n---------------------------------------\n");
    wait_user_reaction();
}

/* file_io.h */

#ifndef __FILE_IO__
#define __FILE_IO__

void writeComplex(char *fname, struct Complex *complex, int count);
int readComplex(char *fname, struct Complex *complex, int count);

#endif

/* file_io.c */

#include "file_io.h"
#include "complex.h"
#include "io.h"

#include <windows.h>

void
writeComplex(char *fname, struct Complex *complex, int count) {
    HANDLE hFile;
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

    BOOL isWritten = FALSE;
    DWORD dwBytesToWrite = sizeof(complex[0]) * count;
    DWORD dwBytesWritten = 0;
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

    BOOL isRead = FALSE;
    DWORD readBytes = 0;
    LPDWORD lpReadBytes = &readBytes;

    DWORD bytesToRead = sizeof(complex[0]) * count;

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