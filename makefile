all: game

game: main.o print_frame.o process_frame.o
	gcc main.o print_frame.o process_frame.o -o game
main: main.c
	gcc -c main.c -o main.o

print_frame: print_frame.c
	gcc -c print_frame.c -o print_frame.o

process_frame: process_frame.c
	gcc -c process_frame.c -o process_frame.o
