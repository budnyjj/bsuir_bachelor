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