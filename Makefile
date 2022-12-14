CC=gcc
CFLAGS=-Wall -Werror -std=c99 -pedantic -c
LFLAGS=-Wall -lSDL2 -lm
DEBUG=-g

all: hangon

hangon: main.o fondo.o paleta.o imagen.o pixel.o ruta.o figura.o teselas.o moto.o ecuaciones.o fisica.o textos.o semaforo.o
	$(CC) $(LFLAGS) $(DEBUG) -o hangon main.o fondo.o paleta.o imagen.o pixel.o ruta.o figura.o teselas.o moto.o ecuaciones.o fisica.o textos.o semaforo.o

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

figura.o: figura.c figura.h
	$(CC) $(CFLAGS) $(DEBUG) -o figura.o figura.c

teselas.o: teselas.c teselas.h imagen.h
	$(CC) $(CFLAGS) $(DEBUG) -o teselas.o teselas.c

moto.o: moto.c moto.h imagen.h
	$(CC) $(CFLAGS) $(DEBUG) -o moto.o moto.c

ecuaciones.o: ecuaciones.c ecuaciones.h
	$(CC) $(CFLAGS) $(DEBUG) -o ecuaciones.o ecuaciones.c

fisica.o: fisica.c fisica.h
	$(CC) $(CFLAGS) $(DEBUG) -o fisica.o fisica.c

textos.o: textos.c textos.h
	$(CC) $(CFLAGS) $(DEBUG) -o textos.o textos.c

semaforo.o: semaforo.c semaforo.h
	$(CC) $(CFLAGS) $(DEBUG) -o semaforo.o semaforo.c

paleta.h: pixel.h

imagen.h: pixel.h

clean:
	rm *.o
