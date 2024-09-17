all: maze
maze: maze.o main.o
	gcc -o maze maze.o main.o
maze.o: maze.c maze.h
	gcc -c maze.c
main.o: main.c maze.c
	gcc -c main.c