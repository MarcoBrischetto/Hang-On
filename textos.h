#ifndef TEXTOS_H
#define TEXTOS_H

#include <stdint.h>
#include "imagen.h"

#define TOP_FILAS       3
#define TOP_COLUMNAS    5

#define SCORE_FILAS     3
#define SCORE_COLUMNAS  7

#define TIME_FILAS      3
#define TIME_COLUMNAS   6

#define GAME_OVER_FILAS     2
#define GAME_OVER_COLUMNAS  16

#define GOAL_FILAS      2
#define GOAL_COLUMNAS   8

extern const uint16_t top_mosaico[TOP_FILAS][TOP_COLUMNAS];
extern const uint8_t top_paleta[TOP_FILAS][TOP_COLUMNAS];

extern const uint16_t score_mosaico[SCORE_FILAS][SCORE_COLUMNAS];
extern const uint8_t score_paleta[SCORE_FILAS][SCORE_COLUMNAS];

extern const uint16_t time_mosaico[TIME_FILAS][TIME_COLUMNAS];
extern const uint8_t time_paleta[TIME_FILAS][TIME_COLUMNAS];

extern const uint16_t game_over_mosaico[GAME_OVER_FILAS][GAME_OVER_COLUMNAS];
extern const uint8_t game_over_paleta[GAME_OVER_FILAS][GAME_OVER_COLUMNAS];

extern const uint16_t goal_mosaico[GOAL_FILAS][GOAL_COLUMNAS];
extern const uint8_t goal_paleta[GOAL_FILAS][GOAL_COLUMNAS];


/*prototipos*/

void escribir_texto(imagen_t *cuadro, char *s, imagen_t *teselas[], size_t x, size_t y, const pixel_t paleta[]);
void escribir_texto_alineacion_derecha(imagen_t *cuadro, char *s, imagen_t *teselas[], size_t x, size_t y, const pixel_t paleta[]);

void generar_textos_estaticos(imagen_t *cuadro, imagen_t *teselas[]);
void generar_textos_variables(imagen_t *cuadro, imagen_t *teselas[], int velocidad, int puntaje, int tiempo_restante);
#endif
