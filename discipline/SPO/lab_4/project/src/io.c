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
    char sign;
    printf("complex number in the format a[+/-]bi: ");
    while (scanf("%lf%[+-]%lf[ij]", &complex.re, &sign, &complex.im) != 3) {
        printf("Input error! The format must be a[+/-]bi: ");
        clear();
    }
    clear();

    if (sign == '-') {
        complex.im = -complex.im;
    }
    return complex;
}

static struct Complex change_complex_form(struct Complex complex) {   
    double mod, phi;
    mod = sqrt(complex.re * complex.re + complex.im * complex.im);
    phi = atan(complex.im / complex.re) * 180 / PI;

    struct Complex result;
    result.re = mod;
    result.im = phi;
    
    return result;
}

void
print_complex(struct Complex complex) {
    struct Complex polar_complex;
    polar_complex = change_complex_form(complex);

    char sign = '+';
    if (complex.im < 0) {
        sign = '-';
        complex.im = -complex.im;
    }

    printf("---  Algebraic form:  -----------------\n");
    printf("%g %c %g*i\n", complex.re, sign, complex.im);

    printf("---  Polar form:  ---------------------\n");
    printf("%g * e^(%g*i)\n", polar_complex.re, polar_complex.im);
    printf("---------------------------------------\n");
}

void 
print_main_user_menu() {
    printf("+--- Choose operation: ---------------+\n");
    printf("|  a --- Add complex numbers          |\n");
    printf("|  s --- Sub complex numbers          |\n");
    printf("|  m --- Mul complex numbers          |\n");
    printf("|  d --- Div complex numbers          |\n");
    printf("|  q --- Quit                         |\n");
    printf("+-------------------------------------+\n");
}