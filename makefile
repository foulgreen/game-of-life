all: game

game: main.c print_frame.o process_frame.o
	gcc main.c print_frame.o process_frame.o -o game

print_frame.o: print_frame.c
	gcc -c print_frame.c

process_frame.o: process_frame.c
	gcc -c process_frame.c

clean:
	rm -f print_frame.o
	rm -f process_frame.o
	rm -f game
