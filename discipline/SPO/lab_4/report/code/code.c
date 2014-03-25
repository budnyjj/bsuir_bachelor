/*  
    authors:        Anashkevich P.S., Budny R.I.
    group number:   120602
    date:           12.03.2014 - 26.03.2014 
*/

/* file: main.c */
#include "ui.h"

int main () {    
    complex_process();
    return 0;
}

/* file: ui.h */
#ifndef __UI_H__
#define __UI_H__

void complex_process();

#endif

/* file: ui.c */
#include "ui.h"
#include "io.h"
#include "complex.h"

#include <stdio.h>

void 
complex_process() {
    struct Complex from, to, result;

    while (1) {
         
        printf("First "); from = input_complex();        
        printf("Second ");  to = input_complex();

        print_user_menu();
        
        switch (getchar()) {
        case 'a':
        case 'A':       
            result = add(from, to);
            print_complex(result);
            break;
        case 's':
        case 'S':
            result = sub(from, to);
            print_complex(result);
            break;
        case 'm':
        case 'M':
            result = mul(from, to);
            print_complex(result);
            break;
        case 'd':
        case 'D':
            result = div(from, to);
            print_complex(result);
            break;
        case 'q':
        case 'Q':
            return;
        default:
            printf("Incorrect input, please choose an exists element\n");
        }
    }
}

/* file: complex.h */
#ifndef __COMPLEX_H__
#define __COMPLEX_H__

struct Complex {
    double re;
    double im;
};

struct Complex add(struct Complex c1, struct Complex c2);
struct Complex sub(struct Complex c1, struct Complex c2);
struct Complex mul(struct Complex c1, struct Complex c2);
struct Complex div(struct Complex c1, struct Complex c2);

#endif

/* file: complex.c */
#include "complex.h"

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
div(struct Complex from, struct Complex to) {
    struct Complex result;
    result.re = (from.re * to.re + from.im * to.im) / (to.re * to.re + to.im * to.im);
    result.im = (from.re * to.im - from.im * to.re) / (to.re * to.re + to.im * to.im);
    return result;
}

/* file: io.h */
#ifndef __IO_H__
#define __IO_H__

void clear();

struct Complex input_complex();
void print_complex(struct Complex complex);

void print_user_menu();

#endif

/* file: io.c */

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
print_user_menu() {
    printf("+--- Choose operation: ---------------+\n");
    printf("|  a --- Add complex numbers          |\n");
    printf("|  s --- Sub complex numbers          |\n");
    printf("|  m --- Mul complex numbers          |\n");
    printf("|  d --- Div complex numbers          |\n");
    printf("|  q --- Quit                         |\n");
    printf("+-------------------------------------+\n");
}