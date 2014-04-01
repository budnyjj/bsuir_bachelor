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

#define complex1_re 1
#define complex1_im 2.2
#define complex2_re -5
#define complex2_im 3

void 
complex_process() {
    struct Complex c1, c2, result;

    c1.re = complex1_re; c1.im = complex1_im;
    c2.re = complex2_re; c2.im = complex2_im;

    while (1) {
        print_user_menu(c1, c2);
        switch (getchar()) {
        case '1':
            printf("Input first complex number.\n");
            c1 = input_complex();
            break;
        case '2':
            printf("Input second complex number.\n");
            c2 = input_complex();
            break;
        
        // complex operations
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
            result = div(c1, c2);
            if (!result.error)
                print_complex(result);
            break;
        case 'q':
        case 'Q':
            return;
        default:
            printf("Incorrect input, please choose an exists element\n");
        }
        clear();
    }
}

/* file: complex.h */
#ifndef __COMPLEX_H__
#define __COMPLEX_H__

struct Complex {
    double re;
    double im;
    int error; // error number
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
    result.error = 0;

    if (!(to.im) && !(to.re)) {
        printf("Invalid operation (devide by zero error)!\n");
        result.error = 1;
    }

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

void print_user_menu(struct Complex c1, struct Complex c2);

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