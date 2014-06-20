#ifndef HELLO_EXPORTS
#define HELLO_API __declspec(dllexport)
#else
#define HELLO_API __declspec(dllimport)
#endif

#ifndef HELLO
#define HELLO

HELLO_API void * hello();

#endif