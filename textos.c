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
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
};

const uint16_t score_mosaico[SCORE_FILAS][SCORE_COLUMNAS] = {
    {0xb0, 0xb1, 0xb1, 0xb1, 0xb1, 0xb1, 0xb2},
    {0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9},
    {0xba, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbc}
};

const uint8_t score_paleta[SCORE_FILAS][SCORE_COLUMNAS] = {
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0}
};


const uint16_t time_mosaico[TIME_FILAS][TIME_COLUMNAS] = {
    {0xa0, 0xa1, 0xa1, 0xa1, 0xa1, 0xa2},
    {0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8},
    {0xa9, 0xaa, 0xaa, 0xaa, 0xaa, 0xab}
};

const uint8_t time_paleta[TIME_FILAS][TIME_COLUMNAS] = {
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0}
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

const uint16_t numeros_mosaico[10][2] = {
    {0x80, 0x81}, //0
    {0x82, 0x83}, //1
    {0x84, 0x85}, //2
    {0x86, 0x87}, //3
    {0x88, 0x89}, //...
    {0x8a, 0x8b},
    {0x8c, 0x8d},
    {0x8e, 0x8f},
    {0x90, 0x91},
    {0x92, 0x93}
};

/*
    funcion: escribir_texto
    dibuja en la imagen cuadro textos mediante teselas

*/

void escribir_texto(imagen_t *cuadro, char *s, imagen_t *teselas[], size_t x, size_t y, const pixel_t paleta[]){

    for(size_t i = 0; s[i] != '\0'; i++)
        imagen_pegar_con_paleta(cuadro, teselas[(uint8_t)s[i]], x + i * ANCHO_TESELA, y, paleta, false);

}

/*
    funcion: escribir_texto_alineacion_derecha
    dibuja en la imagen cuadro textos mediante teselas y los alinea a la derecha

*/

void escribir_texto_alineacion_derecha(imagen_t *cuadro, char *s, imagen_t *teselas[],size_t x, size_t y, const pixel_t paleta[]){

    size_t len = strlen(s);

    for(size_t i = len; i > 0; i--){
        imagen_pegar_con_paleta(cuadro, teselas[(uint8_t)s[len-i]], x - i * ANCHO_TESELA, y, paleta, false);
    }

}

/*
    funcion: escribir_numeros
    dibuja en la imagen cuadro numeros del contador de segundos mediante teselas

*/

static void escribir_numeros(imagen_t *cuadro, int num, imagen_t *teselas[], const uint16_t mosaico_teselas[][2],size_t x, size_t y, const pixel_t paleta[]){

    char str[MAX_STR];

    sprintf(str, "%d", num);

    if(strlen(str) < 2){
        for(size_t i = 0; i < 2; i++)
            imagen_pegar_con_paleta(cuadro, teselas[(uint8_t)mosaico_teselas[0][i]], x, y + i * ALTO_TESELA, paleta, false);

        x+= ANCHO_TESELA;
    }

    for(size_t i = 0; str[i] != '\0'; i++){
        for(size_t j = 0; j < 2; j++)
            imagen_pegar_con_paleta(cuadro, teselas[(uint8_t)mosaico_teselas[str[i] - 0x30][j]], x + i * ANCHO_TESELA, y + j * ALTO_TESELA, paleta, false);
    }

}

/*
    funcion: generar_textos_estaticos
    dibuja en la imagen cuadro los textos estaticos

*/
void generar_textos_variables(imagen_t *cuadro, imagen_t *teselas[], int velocidad, int puntaje, int tiempo_restante){
    char aux[MAX_STR];

    sprintf(aux, "%d", velocidad);
    escribir_texto_alineacion_derecha(cuadro, aux, teselas, 272, 24, paleta_3[6]);

    sprintf(aux, "%d", puntaje);
    escribir_texto_alineacion_derecha(cuadro, aux, teselas, 304, 8, paleta_3[7]);

    escribir_numeros(cuadro, tiempo_restante, teselas, numeros_mosaico, 144, 24, paleta_3[5]);

}

enum textos{
    TOP, TIME, SCORE, TOP_NUM ,STAGE, STAGE_NUM, KM, VELOCIDAD, PUNTAJE
};
/*
typedef struct{
    char *str;
    size_t x;
    size_t y;
    size_t filas;
    size_t columnas;
    const void *mosaico;
    const void *paleta;

}texto_t;
*/
/*
    funcion: generar_textos_estaticos
    dibuja en la imagen cuadro los textos estaticos

*/

void generar_textos_estaticos(imagen_t *cuadro, imagen_t *teselas[]){

    imagen_t *top = generar_mosaico(teselas, paleta_3_identidad, TOP_FILAS, TOP_COLUMNAS, top_mosaico, top_paleta);
    imagen_pegar_con_paleta(cuadro, top, 16, 0, paleta_3[5], false);
    imagen_destruir(top);

    imagen_t *time = generar_mosaico(teselas, paleta_3_identidad, TIME_FILAS, TIME_COLUMNAS, time_mosaico, time_paleta);
    imagen_pegar_con_paleta(cuadro, time, 128, 0, paleta_3[5], false);
    imagen_destruir(time);

    imagen_t *score = generar_mosaico(teselas, paleta_3_identidad, SCORE_FILAS, SCORE_COLUMNAS, score_mosaico, score_paleta);
    imagen_pegar_con_paleta(cuadro, score, 176, 0, paleta_3[5], false);
    imagen_destruir(score);

    escribir_texto(cuadro, "1000000", teselas, 64, 8, paleta_3[8]);
    escribir_texto(cuadro, "STAGE", teselas, 24, 24, paleta_3[5]);
    escribir_texto(cuadro, "1", teselas, 72, 24, paleta_3[6]);

    escribir_texto(cuadro, "SPEED", teselas, 192, 24, paleta_3[6]);
    escribir_texto(cuadro, "KM", teselas, 272, 24, paleta_3[6]);


}

