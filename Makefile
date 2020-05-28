all: program
program: main.o functions.o
	gcc -m32 -o program main.o functions.o -lm
main.o: main.c
	gcc -m32 -std=c99 -c main.c
functions.o: functions.asm
	nasm -f elf32 functions.asm
clear:
	rm *.o