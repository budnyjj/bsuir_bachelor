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

        print_main_user_menu();
        
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