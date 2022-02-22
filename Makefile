CC = gcc
CFLAGS = -Wall -g

SRC = scanner.h testScanner.h lex.h token.h

OBJ = scanner.o testScanner.o
MASTER_OBJ = main.o

MASTER = scanner

OUTPUT = $(MASTER)

all: $(OUTPUT)

%.o: %.c $(STANDARD) $(SRC)
	$(CC) $(CFLAGS) -c $< -o $@

$(MASTER): $(MASTER_OBJ) $(OBJ)
	$(CC) $(CFLAGS) $(MASTER_OBJ) $(OBJ) -o $(MASTER)

clean: 
	rm -f $(OUTPUT) *.o .*buffer 
