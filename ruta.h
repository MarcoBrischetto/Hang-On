#ifndef RUTA_H
#define RUTA_H

#include <stdbool.h>
#include <stddef.h>
#include "imagen.h"

#define ARCHIVO_ROM_RUTA "roms/6840.rom"

enum figura{
    ARBOL, CARTEL, ROCA, BELL, FORUM, DELFIN
};

struct figura_en_ruta {
    enum figura figura;     // Se deja libertad para definir esto como un enum donde corresponda
    size_t paleta;
    int y;
    bool reflejar;
};

struct ruta {
    float radio_curva;
    size_t indice_figura;
};

extern const struct figura_en_ruta figuras_en_ruta[];
extern const struct ruta ruta[4200 + 70];
extern const pixel_t colores_ruta[][16];

/*Prototipos de funciones*/
imagen_t *ruta_cargar_rom();

#endif
