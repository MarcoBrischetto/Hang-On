#ifndef RUTA_H
#define RUTA_H

#include <stdbool.h>
#include <stddef.h>
#include "imagen.h"
#include "figura.h"

#define ARCHIVO_ROM_RUTA "roms/6840.rom"

#define ANCHO_RUTA  512
#define ALTO_RUTA   128

#define ALTO_RECORTADO_RUTA    96


/*como en el pegado de la ruta, la imagen quedaba recortada
 hice una compensacion para evitar partes de la ruta sin dibujar
 */
#define COMPENSACION_CENTRO_RUTA -60
#define COMPENSACION_RECORTE_RUTA 60

#define CAMPO_VISION 60

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
void ruta_dibujar(imagen_t *cuadro, imagen_t *ruta, double *ur, double xm, const struct ruta *r);
void ruta_dibujar_figuras(imagen_t *cuadro, const struct ruta *ruta, double *ur, double x, uint16_t rom[CANTIDAD_VALORES_ROMS], const pixel_t paleta[][16]);

#endif
