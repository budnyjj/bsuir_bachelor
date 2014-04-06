#include "io.h"
#include "complex.h"

#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

void
clear() { while(getchar() != '\n'); }

struct Complex
input_complex() {
    struct Complex complex;
    
    printf("Enter real part: ");
    clear();
    while (!scanf("%lf", &complex.re)) {
        printf("Input error! Try again: ");
        clear();
    }

    printf("Enter imaginary part: ");
    clear();
    while (!scanf("%lf", &complex.im)) {
        printf("Input error! Try again: ");
        clear();
    }

    return complex;
}

static struct Complex change_complex_form(struct Complex complex) {   
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
print_algebraic_complex(struct Complex complex) {
    char sign = '+';
    if (complex.im < 0) {
        sign = '-';
        complex.im = -complex.im;
    }

    printf("%g %c %g*i\n", complex.re, sign, complex.im);
}

static void
print_polar_complex(struct Complex complex) {
    struct Complex polar_complex;
    polar_complex = change_complex_form(complex);

    if (!polar_complex.error)
        printf("%g * e^(%g*i)\n", polar_complex.re, polar_complex.im);
    else
        printf("Indeterminate polar value!\n");
}

void
print_complex(struct Complex complex) {
    printf("+-------------------------------------+\n");
    printf("Result (in algebraic form): ");
    print_algebraic_complex(complex);
    printf("+-------------------------------------+\n");
    printf("Result (in polar form): ");
    print_polar_complex(complex);
    printf("+-------------------------------------+\n");
}

void 
print_user_menu(struct Complex c1, struct Complex c2) {
    printf("+---------- Complex numbers ----------+\n");
    printf("     first  complex number: "); print_algebraic_complex(c1);
    printf("     second complex number: "); print_algebraic_complex(c2);
    printf("+-------------------------------------+\n"
           "|  1 --- Edit  first complex number   |\n"
           "|  2 --- Edit second complex number   |\n"
           "+--- Choose operation: ---------------+\n"
           "|  a --- Add complex numbers          |\n"
           "|  s --- Sub complex numbers          |\n"
           "|  m --- Mul complex numbers          |\n"
           "|  d --- Div complex numbers          |\n"
           "|  q --- Quit                         |\n"
           "+-------------------------------------+\n");
}