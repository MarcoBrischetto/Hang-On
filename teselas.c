#include "teselas.h"

bool leer_teselas(imagen_t *teselas[]){

    uint8_t linea;
    pixel_t pixel;
    uint8_t r, g, b;

    FILE *rom = fopen(ARCHIVO_ROM_R, "rb");

    if(rom == NULL) return false;

    for(size_t i = 0; i < CANTIDAD_TESELAS; i++){
        for(size_t f = 0; f < ALTO_TESELA; f++){

            fread(&linea, 1, 1, rom); //leo una tesela

            for(size_t c = 0; c < ALTO_TESELA; c++){

                //creo un pixel en base a lo leido usando manejo de bits
                pixel = pixel3_crear((linea >> (SHIFT_TESELA - c)) &0x1, 0, 0);

                imagen_set_pixel(teselas[i], c, f, pixel);

            }
        }
    }

    if(fclose(rom)) return false;

    rom = fopen(ARCHIVO_ROM_G, "rb");

    if(rom == NULL) return false;

    for(size_t i = 0; i < CANTIDAD_TESELAS; i++){
        for(size_t f = 0; f < ALTO_TESELA; f++){

            fread(&linea, 1, 1, rom);

            for(size_t c = 0; c < ALTO_TESELA; c++){

                pixel = imagen_get_pixel(teselas[i], c, f);

                pixel3_a_rgb(pixel ,&r, &g, &b);

                pixel = pixel3_crear(r, (linea >> (SHIFT_TESELA - c)) &0x1, b);

                imagen_set_pixel(teselas[i], c, f, pixel);

            }
        }
    }

    if(fclose(rom)) return false;

    rom = fopen(ARCHIVO_ROM_B, "rb");

    if(rom == NULL) return false;

    for(size_t i = 0; i < CANTIDAD_TESELAS; i++){
        for(size_t f = 0; f < ALTO_TESELA; f++){

            fread(&linea, 1, 1, rom);

            for(size_t c = 0; c < ALTO_TESELA; c++){

                pixel = imagen_get_pixel(teselas[i], c, f);

                pixel3_a_rgb(pixel ,&r, &g, &b);

                pixel = pixel3_crear(r, g, (linea >> (SHIFT_TESELA - c)) &0x1);

                imagen_set_pixel(teselas[i], c, f, pixel);

            }
        }
    }

    if(fclose(rom)) return false;

    return true;
}

/*
    funcion: generar_mosaicos
    crea un mosaico a partir de un vector de teselas y paletas
*/

imagen_t *generar_mosaico(imagen_t *teselas[], const pixel_t paleta[][8], size_t filas, size_t columnas, const uint16_t mosaico_teselas[filas][columnas], const uint8_t mosaico_paletas[filas][columnas]){

    imagen_t *img = imagen_generar(columnas*ANCHO_TESELA, filas*ALTO_TESELA, 0);

    if(img == NULL) return NULL;

    for(size_t f = 0; f < filas; f++){
        for(size_t c = 0; c < columnas; c++){

            imagen_pegar_con_paleta(img, teselas[mosaico_teselas[f][c]], c*ANCHO_TESELA, f*ALTO_TESELA, paleta[mosaico_paletas[f][c]]);

        }
    }

    return img;
}

/*
    funcion: cargar_teselas
    Carga en el array teselas, las teselas de la rom
*/

bool cargar_teselas(imagen_t *teselas[CANTIDAD_TESELAS]){

    for(size_t i = 0; i < CANTIDAD_TESELAS; i++)
        teselas[i] = imagen_generar(ANCHO_TESELA, ALTO_TESELA, 0);

    if(! leer_teselas(teselas)) {

        for(size_t i = 0; i < CANTIDAD_TESELAS; i++)
            imagen_destruir(teselas[i]);

        return false;
    }

    return true;

}

/*
    funcion: liberar_teselas
    libera la memoria asociada al array de las teselas
*/

void liberar_teselas(imagen_t *teselas[CANTIDAD_TESELAS]){

    for(size_t i = 0; i < CANTIDAD_TESELAS; i++)
            imagen_destruir(teselas[i]);

}
