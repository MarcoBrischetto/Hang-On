#include "textos.h"
#include "teselas.h"
#include "string.h"
#include "imagen.h"
#include "paleta.h"

const uint16_t top_mosaico[TOP_FILAS][TOP_COLUMNAS] = {
    {0x94, 0x95, 0x95, 0x95, 0x96},
    {0x97, 0x98, 0x99, 0x9a, 0x9b},
    {0x9c, 0x9d, 0x9d, 0x9d, 0x9e}
};

const uint8_t top_paleta[TOP_FILAS][TOP_COLUMNAS] = {
    {5, 5, 5, 5, 5},
    {5, 5, 5, 5, 5},
    {5, 5, 5, 5, 5}
};

const uint16_t score_mosaico[SCORE_FILAS][SCORE_COLUMNAS] = {
    {0xb0, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb2},
    {0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9},
    {0xba, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbc}
};

const uint8_t score_paleta[SCORE_FILAS][SCORE_COLUMNAS] = {
    {5, 5, 5, 5, 5, 5, 5},
    {5, 5, 5, 5, 5, 5, 5},
    {5, 5, 5, 5, 5, 5, 5}
};


const uint16_t time_mosaico[TIME_FILAS][TIME_COLUMNAS] = {
    {0xa0, 0xa1, 0xa1, 0xa1, 0xa1, 0xa2},
    {0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8},
    {0xa9, 0xaa, 0xaa, 0xaa, 0xaa, 0xab}
};

const uint8_t time_paleta[TIME_FILAS][TIME_COLUMNAS] = {
    {5, 5, 5, 5, 5, 5},
    {5, 5, 5, 5, 5, 5},
    {5, 5, 5, 5, 5, 5}
};

const uint16_t game_over_mosaico[GAME_OVER_FILAS][GAME_OVER_COLUMNAS] = {
    {0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f},
    {0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f}
};

const uint8_t game_over_paleta[GAME_OVER_FILAS][GAME_OVER_COLUMNAS] = {
    {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
    {7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7}
};

const uint16_t goal_mosaico[GOAL_FILAS][GOAL_COLUMNAS] = {
    {0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7},
    {0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef}
};

const uint8_t goal_paleta[GOAL_FILAS][GOAL_COLUMNAS] = {
    {5, 5, 5, 5, 5, 5, 5, 5},
    {5, 5, 5, 5, 5, 5, 5, 5}
};


void escribir_texto(imagen_t *cuadro, char *s, imagen_t *teselas[], size_t x, size_t y, const pixel_t paleta[]){

    for(size_t i = 0; s[i] != '\0'; i++)
        imagen_pegar_con_paleta(cuadro, teselas[(uint8_t)s[i]], x + i * ANCHO_TESELA, y, paleta, false);

}

void escribir_texto_alineacion_derecha(imagen_t *cuadro, char *s, imagen_t *teselas[], size_t x, size_t y, const pixel_t paleta[]){

    size_t len = strlen(s);

    for(size_t i = len; i > 0; i--){
        imagen_pegar_con_paleta(cuadro, teselas[(uint8_t)s[len-i]], x - i * ANCHO_TESELA, y, paleta, false);
    }

}

void generar_textos_variables(imagen_t *cuadro, imagen_t *teselas[], int velocidad, int puntaje, int tiempo_restante){
    char aux[MAX_STR];

    sprintf(aux, "%d", velocidad);
    escribir_texto_alineacion_derecha(cuadro, aux, teselas, 272, 24, paleta_3[6]);
    sprintf(aux, "%d", puntaje);

    escribir_texto_alineacion_derecha(cuadro, aux, teselas, 304, 8, paleta_3[7]);
    //escribir_texto_alineacion_derecha(cuadro, "1", teselas, 72, 24, paleta_3[6]);

}

enum textos{
    TOP, TIME, SCORE, TOP_NUM ,STAGE, STAGE_NUM, KM, VELOCIDAD, PUNTAJE
};

typedef struct{
    char *str;
    size_t x;
    size_t y;
    size_t filas;
    size_t columnas;
    const void *mosaico;
    const void *paleta;

}texto_t;

texto_t lista_textos[] = {
    [TOP] = {NULL, 16, 0, TOP_FILAS, TOP_COLUMNAS, top_mosaico, top_paleta},

};

void generar_textos_estaticos(imagen_t *cuadro, imagen_t *teselas[]){

    /*TODO hacerlo iterativo*/
/*
    imagen_t *top = generar_mosaico(teselas, paleta_3, TOP_FILAS, TOP_COLUMNAS, top_mosaico, top_paleta);
    imagen_pegar(cuadro, top, 16, 0, false);
    imagen_destruir(top);
*/
    /*
    size_t i = 0;
    imagen_t *txt = generar_mosaico(teselas, paleta_3, lista_textos[i].filas, lista_textos[i].columnas, (const uint16_t (*)[lista_textos[i].columnas])lista_textos[i].mosaico, (const uint8_t (*)[lista_textos[i].columnas])lista_textos[i].paleta);
    imagen_pegar(cuadro, txt, lista_textos[i].x, lista_textos[i].y, false);
    imagen_destruir(txt);
*/
    imagen_t *time = generar_mosaico(teselas, paleta_3, TIME_FILAS, TIME_COLUMNAS, time_mosaico, time_paleta);
    imagen_pegar(cuadro, time, 128, 0, false);
    imagen_destruir(time);

    imagen_t *score = generar_mosaico(teselas, paleta_3, SCORE_FILAS, SCORE_COLUMNAS, score_mosaico, score_paleta);
    imagen_pegar(cuadro, score, 176, 0, false);
    imagen_destruir(score);


    escribir_texto(cuadro, "1000000", teselas, 64, 8, paleta_3[5]);
    escribir_texto(cuadro, "STAGE", teselas, 24, 24, paleta_3[5]);
    escribir_texto(cuadro, "1", teselas, 72, 24, paleta_3[6]);

    escribir_texto(cuadro, "SPEED", teselas, 192, 24, paleta_3[6]);
    escribir_texto(cuadro, "KM", teselas, 272, 24, paleta_3[6]);


/*
    imagen_t *game_over = generar_mosaico(teselas, paleta_3, GAME_OVER_FILAS, GAME_OVER_COLUMNAS, game_over_mosaico, game_over_paleta);
    imagen_pegar(cuadro, game_over, 80, 10, false);
    imagen_destruir(game_over);

    imagen_t *goal = generar_mosaico(teselas, paleta_3, GOAL_FILAS, GOAL_COLUMNAS, goal_mosaico, goal_paleta);
    imagen_pegar(cuadro, goal, 80, 40, false);
    imagen_destruir(goal);
*/
}

