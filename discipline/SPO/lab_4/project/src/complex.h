#ifndef __COMPLEX_H__
#define __COMPLEX_H__

struct Complex {
	double re;
	double im;
};

struct Complex add(struct Complex c1, struct Complex c2);
struct Complex sub(struct Complex c1, struct Complex c2);
struct Complex mul(struct Complex c1, struct Complex c2);
struct Complex div(struct Complex c1, struct Complex c2);

#endif