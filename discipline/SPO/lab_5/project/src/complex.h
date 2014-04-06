#ifndef __COMPLEX__
#define __COMPLEX__

struct Complex {
    double re;
    double im;
    int error; // error number
};

struct Complex add(struct Complex c1, struct Complex c2);
struct Complex sub(struct Complex c1, struct Complex c2);
struct Complex mul(struct Complex c1, struct Complex c2);
struct Complex div(struct Complex c1, struct Complex c2);

#endif