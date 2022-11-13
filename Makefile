CC=gcc
CFLAGS=-Wall -Werror -std=c99 -pedantic -c
LFLAGS=-Wall -lSDL2
DEBUG=-g

all: hangon

hangon: main.o fondo.o paleta.o imagen.o pixel.o ruta.o
	$(CC) $(LFLAGS) $(DEBUG) -o hangon main.o fondo.o paleta.o imagen.o pixel.o ruta.o

main.o: main.c config.h imagen.h
	$(CC) $(CFLAGS) $(DEBUG) -o main.o main.c

fondo.o: fondo.c fondo.h
	$(CC) $(CFLAGS) $(DEBUG) -o fondo.o fondo.c

paleta.o: paleta.c paleta.h
	$(CC) $(CFLAGS) $(DEBUG) -o paleta.o paleta.c

imagen.o: imagen.c imagen.h
	$(CC) $(CFLAGS) $(DEBUG) -o imagen.o imagen.c

pixel.o: pixel.c pixel.h
	$(CC) $(CFLAGS) $(DEBUG) -o pixel.o pixel.c

ruta.o: ruta.c ruta.h
	$(CC) $(CFLAGS) $(DEBUG) -o ruta.o ruta.c

paleta.h: pixel.h

imagen.h: pixel.h

clean:
	rm *.o
