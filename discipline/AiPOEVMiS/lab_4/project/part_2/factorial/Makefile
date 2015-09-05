default: lib asm

lib: 
	gcc -g -O0 -c factorial.c -o bin/factorial.o

asm:
	nasm -g -f elf64 -o bin/main.o main.asm
	ld -dynamic-linker /lib/ld-linux-x86-64.so.2 /usr/lib64/crt1.o /usr/lib64/crti.o -lc\
	   bin/main.o bin/factorial.o /usr/lib64/crtn.o -o bin/main 
