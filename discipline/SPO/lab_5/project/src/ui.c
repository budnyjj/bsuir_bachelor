#include "ui.h"
#include "io.h"
#include "complex.h"

#include <stdio.h>

#define COMPLEX1_RE 1
#define COMPLEX1_RE 2.2
#define COMPLEX2_RE -5
#define COMPLEX2_IM 3

void
complex_process() {
    struct Complex c1, c2, result;

    c1.re = COMPLEX1_RE; c1.im = COMPLEX1_IM;
    c2.re = COMPLEX2_RE; c2.im = COMPLEX2_IM;

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