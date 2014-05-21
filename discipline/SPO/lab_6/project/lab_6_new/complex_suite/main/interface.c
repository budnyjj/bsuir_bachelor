#include <interface.h>
#include <complex.h>
#include <complex_io.h>
#include <io.h>

#include <stdlib.h>
#include <stdio.h>

#define INPUT_SOURCE "file.complex"
#define OUTPUT_SOURCE "file.complex"

#define COUNT_ELEMENTS_TO_WRITE_DEFAULT 2
#define COUNT_ELEMENTS_TO_READ_DEFAULT 50
#define COUNT_ELEMENTS_TO_READ_MAX 100000

static int get_index_to_edit_complex(int count_of_elements);
static int get_count_of_elements_to_rw(int count_of_elements);
static int get_new_count_to_read();
static int realloc_complex(struct Complex **complex, int *size, double coeff);

struct Complex *
write_file_interface(struct Complex *complex, int *size, int *count_of_elements) {
    int count_elements_to_write = COUNT_ELEMENTS_TO_WRITE_DEFAULT;
    char file_source[] = OUTPUT_SOURCE;

    while (1) {
		char choice;
        print_write_file_menu(complex, *count_of_elements, count_elements_to_write, file_source);
        choice = getchar();
        clear_input();
        switch (choice) {
        case 'c':
        case 'C':
            count_elements_to_write = get_count_of_elements_to_rw(*count_of_elements);
            break;
        case 'e':
        case 'E':
            if (*count_of_elements > 0) {
                int index = get_index_to_edit_complex(*count_of_elements);
                printf("Input new complex number\n");
                complex[index] = input_complex();
            }
            else {
                printf("No have items to change!\n");
                wait_user_reaction();
            }
            break;
        case 'a':
        case 'A':
        {
            int realloc_error = 0;
            if (*count_of_elements >= *size) {
                realloc_error = realloc_complex(&complex, size, 2.0);
            }
            if (!realloc_error) {
                printf("Please, input new complex number.\n");
                complex[(*count_of_elements)++] = input_complex();
            }
            else {
                printf("Impossible to add element. No have memory!\n");
                wait_user_reaction();
            }
            break;
        }
        case 'd':
        case 'D':
        {
            if (*count_of_elements > 0) {
                if (*count_of_elements <= ((*size) * 0.5)) {
                    realloc_complex(&complex, size, 0.5);
                }
                (*count_of_elements)--;
            }
            else {
                printf("Array of complex numbers is empty!\n");
                wait_user_reaction();
            }
            break;
        }
        case 'w':
        case 'W':
        {
            if (*count_of_elements >= count_elements_to_write) {
                writeComplex(file_source, complex, count_elements_to_write);
                return complex;
            }
            else {
                printf("Change count of elements to write!\n");
                wait_user_reaction();
                break;
            }
        }
        case 'b':
        case 'B':
            return complex;
        default:
            printf("Incorrect input, please choose an existing element\n");
        }
    }
}

struct Complex *
read_file_interface(struct Complex *complex, int *size, int *count_of_elements) {
    int count_elements_to_read = COUNT_ELEMENTS_TO_READ_DEFAULT;
    char file_source[] = INPUT_SOURCE;

    while (1) {
		char choice;
        print_read_file_menu(file_source, count_elements_to_read);
        choice = getchar();
        clear_input();
        switch (choice) {
        case 'c':
        case 'C':
            count_elements_to_read = get_count_of_elements_to_rw(COUNT_ELEMENTS_TO_READ_MAX);
            break;
        case 'r':
        case 'R':
        {            
            int realloc_error = 0;
            while (count_elements_to_read > *size) {
                realloc_error = realloc_complex(&complex, size, 2.0);
                if (realloc_error) {
                    return complex;
                }
            }

            if (!realloc_error) {
                int read_elements = 0;
                read_elements = readComplex(file_source, complex, count_elements_to_read);
                *count_of_elements = read_elements;

                if (read_elements) {
                    print_read_results(complex, read_elements);
                    while (read_elements <= ((*size)*0.5)) {
                        realloc_complex(&complex, size, 0.5);
                    }
                }

                return complex;
            }
            break;
        }
        case 'b':
        case 'B':
            return complex;
        default:
            printf("Incorrect input, please choose an existing element\n");
        }
    }
}

void
change_complex_interface(struct Complex *c, struct Complex *source_array, int count_of_elements) {
    while (1) {
		char choice;
        print_change_complex_menu();
        choice = getchar();
        clear_input();
        switch (choice) {
        case 'e':
        case 'E':
            printf("Input new complex number.\n");
            *c = input_complex();
            return;
        case 'c':
        case 'C':
			{
				if (count_of_elements > 0) {
					int index;
					print_complex_array(source_array, count_of_elements);
					index = get_index_to_edit_complex(count_of_elements);
					*c = source_array[index];
		        }
	            else {
					printf("No have existing items!\n");
					wait_user_reaction();
				}
			}
            break;
        case 'b':
        case 'B':
            return;
        default:
            printf("Incorrect input, please choose an existing element\n");
        }
    }
}

static int
get_index_to_edit_complex(int count_of_elements) {
    int index = 0;
    printf("Choose some index:\n");
    while (!scanf("%d", &index) || (index < 0) || (index > count_of_elements - 1)) {
        printf("Input incorrect! Index interval: [0; %d]\n"
               "Please, try again: ", count_of_elements - 1);
        clear_input();
    }
    clear_input();
    return index;
}

static int
get_count_of_elements_to_rw(int count_of_elements) {
    int new_count = 0;
    printf("Input new count of elements: ");
    while (!scanf("%d", &new_count) || (new_count < 0) || (new_count > count_of_elements)) {
        printf("Input incorrect! Count interval: [0; %d]\n"
               "Please, try again: ", count_of_elements);
        clear_input();
    }
    clear_input();
    return new_count;
}

static int
realloc_complex(struct Complex **complex, int *size, double coeff) {
    struct Complex * new_complex = 0;
    new_complex = (struct Complex *) realloc(*complex, (int)(coeff * (*size) * sizeof(struct Complex)));

    if (new_complex) {
        (*size) = (int) ((*size) * coeff);
        *complex = new_complex;
        return 0;
    }
    else {
        printf("Realloc error!\n");
        wait_user_reaction();
        return 1;
    }
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
print_read_results(struct Complex *complex, int count) {
    printf("------------- Read results ------------\n");
    printf("  Count of read elements: %d", count);
    print_complex_array(complex, count);
    printf("---------------------------------------\n");
    wait_user_reaction();
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