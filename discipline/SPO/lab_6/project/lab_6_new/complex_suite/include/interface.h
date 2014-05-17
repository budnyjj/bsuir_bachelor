#ifndef __INTERFACE__
#define __INTERFACE__

struct Complex * write_file_interface(struct Complex *complex, int *size, int *count_of_elements);
struct Complex * read_file_interface(struct Complex *complex, int *size, int *count_of_elements);

void print_write_file_menu(struct Complex *complex, int count_all_elements, int count_elements_to_write, char *file_source);
void print_main_menu(struct Complex c1, struct Complex c2);
void print_read_results(struct Complex *complex, int count);

void change_complex_interface(struct Complex *c, struct Complex *source_array, int size);

void print_read_file_menu(char *file_source, int count_elements_to_read);
void print_change_complex_menu();

#endif