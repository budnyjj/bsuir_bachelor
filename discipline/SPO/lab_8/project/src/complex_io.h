#ifndef __COMPLEX_IO__
#define __COMPLEX_IO__

int input_complex(struct Complex*);

void print_algebraic_form(struct Complex complex);
void print_polar_form(struct Complex c);

void print_complex(struct Complex complex);
void print_complex_array(struct Complex *complex, int count);


#endif