all: game process_frame_test test

game: main.c print_frame.o process_frame.o
	gcc main.c print_frame.o process_frame.o -o game

print_frame.o: print_frame.c
	gcc -c print_frame.c

process_frame.o: process_frame.c
	gcc -c process_frame.c

process_frame_test: process_frame_test.c process_frame.o
	gcc process_frame_test.c process_frame.o -o process_frame_test

# PHONY targets
.PHONY: test clean help

test: process_frame_test
	./process_frame_test $(SEED)

clean:
	rm -f print_frame.o
	rm -f process_frame.o
	rm -f game

help:
	@echo "Help:"
	@echo "	Useful targets: clean, test, game, and help"
	@echo "	The variable SEED will be used for any needed randomness"
	@echo "	Use make variables like this 'make test SEED=293029'"
