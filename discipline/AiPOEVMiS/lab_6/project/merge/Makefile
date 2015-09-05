default: cpp asm link

cpp:
	g++ -O0 -g -c src/merge.cpp `Magick++-config --cppflags --cxxflags --ldflags --libs` -o obj/merge.o 

asm:
	nasm -g -f elf64 -o obj/merge_raw.o src/merge_raw.asm

link:
	g++ -O0 -g obj/merge.o obj/merge_raw.o `Magick++-config --cppflags --cxxflags --ldflags --libs` -o bin/merge
