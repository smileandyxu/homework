CC = gcc

LIBS     = -static-libstdc++ -static-libgcc -g3
OBJ      = sum.o
INCS     = -I
BIN      = sum.exe
CFLAGS   = $(INCS) -g3

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(LIBS)

sum.o: sum.c
	$(CC) -c sum.c -o sum.o $(CFLAGS)

clean: clean-custom
	rm -f $(OBJ) $(BIN)

