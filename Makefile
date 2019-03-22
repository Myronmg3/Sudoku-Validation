TARG=sudoku
SRCS=main.cc board.cc
OBJS=main.o board.o
CC=g++
FLAGS= -Wall -g

$(TARG): $(OBJS)
	$(CC) $(FLAGS) -o $(TARG) $(OBJS)

main.o: main.cc board.cc board.hh
	$(CC) $(FLAGS) -c main.cc

board.o: board.cc board.hh
	$(CC) $(FLAGS) -c board.cc

clean:
	rm *.o
