#ifndef __INTERFACE__
#define __INTERFACE__

struct Complex * write_file_interface(struct Complex *complex, int *size, int *count_of_elements);
struct Complex * read_file_interface(struct Complex *complex, int *size, int *count_of_elements);

void change_complex_interface(struct Complex *c, struct Complex *source_array, int size);

#endif