CC=gcc
FLAGS= -Wall -Werror -Wextra

all: graph

clean:
	rm *.o plot

rebuild: clean all

graph: graph.o parser.o calculator.o stack.o translator.o plot.o token.o utils.o stack_double.o
	$(CC) $(FLAGS) *.o -lm -o plot
