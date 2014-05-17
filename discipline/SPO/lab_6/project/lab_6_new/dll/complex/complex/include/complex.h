#ifdef DLL_EXPORTS
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif

#ifndef __COMPLEX__
#define __COMPLEX__

struct Complex {
    double re;
    double im;
};

struct Complex DLL_API add(struct Complex c1, struct Complex c2);
struct Complex DLL_API sub(struct Complex c1, struct Complex c2);
struct Complex DLL_API mul(struct Complex c1, struct Complex c2);
struct Complex DLL_API division(struct Complex c1, struct Complex c2, int * error);

#endif