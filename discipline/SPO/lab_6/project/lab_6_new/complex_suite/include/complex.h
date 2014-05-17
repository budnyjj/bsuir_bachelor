#ifndef __COMPLEX__
#define __COMPLEX__

struct Complex {
    double re;
    double im;
};

struct Complex add(struct Complex c1, struct Complex c2);
struct Complex sub(struct Complex c1, struct Complex c2);
struct Complex mul(struct Complex c1, struct Complex c2);
struct Complex division(struct Complex c1, struct Complex c2, int * error);

void writeComplex(char *fname, struct Complex *complex, int count);
int readComplex(char *fname, struct Complex *complex, int count);

#endif