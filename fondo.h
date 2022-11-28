#ifndef FONDO_H
#define FONDO_H

#include <stdint.h>
#include "teselas.h"
#include "ruta.h"

#define FONDO1_FILAS 2
#define FONDO1_COLUMNAS 216
#define FONDO2_FILAS 8
#define FONDO2_COLUMNAS 152

#define FONDO_X_INICIAL 320
#define FONDO1_Y    64
#define FONDO2_Y    112

extern const uint8_t fondo1_paleta[FONDO1_FILAS][FONDO1_COLUMNAS];
extern const uint16_t fondo1_mosaico[FONDO1_FILAS][FONDO1_COLUMNAS];
extern const uint8_t fondo2_paleta[FONDO2_FILAS][FONDO2_COLUMNAS];
extern const uint16_t fondo2_mosaico[FONDO2_FILAS][FONDO2_COLUMNAS];

void liberar_teselas(imagen_t *teselas[CANTIDAD_TESELAS]);
imagen_t *generar_pasto();
int desplazamiento_fondo(int xm, int xm_anterior, const struct ruta *r);

#endif
