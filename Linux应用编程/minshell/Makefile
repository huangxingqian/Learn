.PHONY:clean
CC=gcc
CFLAGS=-Wall -g
BIN=minshell
OBJ=main.o parse.o init.o

$(BIN):$(OBJ)
	$(CC) $(CFLAGS) $^ -o $@
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@
clean：
	rm -f *.o $(OBJ)
