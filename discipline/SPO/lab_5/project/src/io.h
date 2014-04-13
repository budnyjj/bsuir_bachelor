#ifndef __IO__
#define __IO__

void clear_input();
void wait_user_reaction();

struct Complex input_complex();

void print_complex(struct Complex complex);
void print_complex_array(struct Complex *complex, int count);
void print_read_results(struct Complex *complex, int count);

void print_write_file_menu(struct Complex *complex, int count_all_elements, int count_elements_to_write, char *file_source);
void print_read_file_menu(char *file_source, int count_elements_to_read);

void print_main_menu(struct Complex c1, struct Complex c2);
void print_change_complex_menu();

void print_rw_message(char *operation_result);

#endif