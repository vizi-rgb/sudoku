CFLAGS=-pedantic -Wall -Wextra -ggdb -lncurses

all: main.o sudoku.o
	$(CC) $^ $(CFLAGS) -o main

%.o: %.c
	$(CC) $(CFLAGS) -c $^  

.PHONY: clean

clean:
	rm *.o main
