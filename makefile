# Nome do compilador
CC = gcc

# Flags do compilador
CFLAGS = -Wall -Wextra -std=c99

# Nome do arquivo executável
TARGET = teste

# Regras principais
all: $(TARGET)

$(TARGET): maze.o main.o
	$(CC) -o $(TARGET) maze.o main.o

maze.o: maze.c maze.h
	$(CC) $(CFLAGS) -c maze.c

main.o: main.c maze.h
	$(CC) $(CFLAGS) -c main.c

# Limpa os arquivos compilados
clean:
	del *.o $(TARGET).exe
