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

