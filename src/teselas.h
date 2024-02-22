#ifndef TESELAS_H
#define TESELAS_H

#include "imagen.h"
//#include <stdbool.h>

#define CANTIDAD_TESELAS 4096
#define ANCHO_TESELA 8
#define ALTO_TESELA 8
#define SHIFT_TESELA 7

#define ARCHIVO_ROM_R   "roms/6841.rom"
#define ARCHIVO_ROM_G   "roms/6842.rom"
#define ARCHIVO_ROM_B   "roms/6843.rom"

bool leer_teselas(imagen_t *teselas[]);
imagen_t *generar_mosaico(imagen_t *teselas[], const pixel_t paleta[][8], size_t filas, size_t columnas, const uint16_t mosaico_teselas[filas][columnas], const uint8_t mosaico_paletas[filas][columnas]);
bool cargar_teselas(imagen_t *teselas[CANTIDAD_TESELAS]);
void liberar_teselas(imagen_t *teselas[CANTIDAD_TESELAS]);

#endif
