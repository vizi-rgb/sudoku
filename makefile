CFLAGS=-pedantic -Wall -Wextra -ggdb -lncurses

all: main.o sudoku.o control.o solver.o
	$(CC) $^ $(CFLAGS) -o main

anim: sudoku.o control.o solver.o 
	$(CC) main.c $(CFLAGS) -DANIM -c
	$(CC) $^ main.o $(CFLAGS) -o main

%.o: %.c
	$(CC) $(CFLAGS) -c $^  

.PHONY: clean

clean:
	rm *.o main
