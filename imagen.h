#ifndef IMAGEN_H
#define IMAGEN_H

#include "pixel.h"
#include <stddef.h>
#include <stdio.h>

#define MAX_STR 100

typedef struct imagen imagen_t;

void imagen_destruir(imagen_t *imagen);
imagen_t *imagen_generar(size_t ancho, size_t alto, pixel_t valor);
imagen_t *imagen_leer_pgm();
void imagen_imprimir_pgm(const imagen_t *imagen);
void imagen_pegar(imagen_t *destino, const imagen_t *origen, int x, int y);
imagen_t *imagen_escalar(const imagen_t *origen, size_t ancho_destino, size_t alto_destino);
imagen_t *imagen_reflejar(imagen_t *im);
void imagen_pegar_con_paleta(imagen_t *destino, const imagen_t *origen, int x, int y, const pixel_t paleta[]);
void imagen_escribir_ppm(const imagen_t *im, FILE *fo, void (*pixel_a_rgb)(pixel_t, uint8_t *, uint8_t *, uint8_t *));
bool imagen_guardar_ppm(const imagen_t *im, const char *fn, void (*pixel_a_rgb)(pixel_t, uint8_t *, uint8_t *, uint8_t *));
void imagen_a_textura(const imagen_t *im, uint16_t *v);

size_t imagen_get_ancho(const imagen_t *im);
size_t imagen_get_alto(const imagen_t *im);
pixel_t imagen_get_pixel(const imagen_t *im, size_t x, size_t y);

bool imagen_set_pixel(const imagen_t *im, size_t x, size_t y, pixel_t p);

#endif //IMAGEN_H
