CC = gcc
SRC = $(wildcard src/backend/*.c) $(wildcard src/frontend/*.c) $(wildcard src/test/*.c)
SRCT = $(wildcard src/backend/*.c) $(wildcard src/test/*.c)
SRCA = $(wildcard src/backend/*.c) $(wildcard src/frontend/*.c)
OBJ = $(SRC:.c=.o)
OBJT = $(SRCT:.c=.o)
OBJA = $(SRCA:.c=.o)
CFLAGS = -lncurses
BIN = ecard
TEST = test

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)


.PHONY: test all app
all: $(OBJ)
	$(CC) -o $(BIN) $(OBJA) $(CFLAGS)
	$(CC) -o $(TEST) $(OBJT) $(CFLAGS)

test: $(OBJ)
	$(CC) -o $(TEST) $(OBJT) $(CFLAGS)

app: $(OBJ)
	$(CC) -o $(TEST) $(OBJA) $(CFLAGS)
clean: $(OBJ)
	@rm $(OBJ) $(BIN) $(TEST)