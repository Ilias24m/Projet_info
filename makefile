# Variables
CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c11
OBJ = mySlayProg.o snakeAPI.o clientAPI.o snakestruct.o
TARGET = main

# Règles
$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

snakestruct.o: snakestruct.c snakestruct.h
	$(CC) $(CFLAGS) -c snakestruct.c -o snakestruct.o

snakeAPI.o: snakeAPI.c snakeAPI.h
	$(CC) $(CFLAGS) -c snakeAPI.c -o snakeAPI.o

clientAPI.o: clientAPI.c clientAPI.h
	$(CC) $(CFLAGS) -c clientAPI.c -o clientAPI.o

mySlayProg.o: mySlayProg.c
	$(CC) $(CFLAGS) -c mySlayProg.c -o mySlayProg.o

clean:
	rm -f $(OBJ) $(TARGET)

