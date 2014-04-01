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