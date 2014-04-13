#ifndef __INTERFACE__
#define __INTERFACE__

void write_file_interface(struct Complex *complex, int *size, int *count_of_elements);
void read_file_interface(struct Complex *complex, int *size, int *count_of_elements);

void change_complex_interface(struct Complex *c, struct Complex *source_array, int size);

#endif