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