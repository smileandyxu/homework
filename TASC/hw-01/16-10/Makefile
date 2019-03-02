CC = gcc
IDIR = include
LDIR = lib

LIBS     = -L"lib" -static-libstdc++ -static-libgcc -g3
OBJ      = teach.o lib/exceptio.o lib/genlib.o lib/random.o lib/simpio.o lib/strlib.o
INCS     = -I"./include"
BIN      = teach.exe
CFLAGS   = $(INCS) -g3

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(LIBS)

teach.o: teach.c
	$(CC) -c teach.c -o teach.o $(CFLAGS)

lib/exceptio.o: lib/exceptio.c
	$(CC) -c lib/exceptio.c -o lib/exceptio.o $(CFLAGS)

lib/genlib.o: lib/genlib.c
	$(CC) -c lib/genlib.c -o lib/genlib.o $(CFLAGS)

lib/random.o: lib/random.c
	$(CC) -c lib/random.c -o lib/random.o $(CFLAGS)

lib/simpio.o: lib/simpio.c
	$(CC) -c lib/simpio.c -o lib/simpio.o $(CFLAGS)

lib/strlib.o: lib/strlib.c
	$(CC) -c lib/strlib.c -o lib/strlib.o $(CFLAGS)

clean: clean-custom
	rm -f $(OBJ) $(BIN)

