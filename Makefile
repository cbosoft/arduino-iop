CC = gcc
CFLAGS = -Wall -Wextra
OBJ = src/main.o

iop: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@
