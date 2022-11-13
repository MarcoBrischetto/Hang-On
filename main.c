#include <SDL2/SDL.h>
#include <stdbool.h>

#include "config.h"
#include "imagen.h"
#include "ruta.h"
#include "paleta.h"
#include "fondo.h"

bool leer_teselas(imagen_t *teselas[]);
imagen_t *generar_mosaico(imagen_t *teselas[], const pixel_t paleta[][8], size_t filas, size_t columnas, const uint16_t mosaico_teselas[filas][columnas], const uint8_t mosaico_paletas[filas][columnas]);
bool cargar_teselas(imagen_t *teselas[CANTIDAD_TESELAS]);
void liberar_teselas(imagen_t *teselas[CANTIDAD_TESELAS]);
imagen_t *generar_pasto();


int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event event;

    SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Hang-On");

    SDL_Texture * texture = SDL_CreateTexture(renderer,
    SDL_PIXELFORMAT_RGB444, SDL_TEXTUREACCESS_STATIC, VENTANA_ANCHO, VENTANA_ALTO);
    uint16_t canvas[VENTANA_ALTO * VENTANA_ANCHO];

    int dormir = 0;

    // BEGIN código del alumno
    double x = -10;
    bool mover = false;

    imagen_t *teselas[CANTIDAD_TESELAS];
    cargar_teselas(teselas);


    // END código del alumno

    unsigned int ticks = SDL_GetTicks();
    while(1) {

        if(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                break;
            // BEGIN código del alumno
            if (event.type == SDL_KEYDOWN) {
                // Se apretó una tecla
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        mover = true;
                        break;
                    case SDLK_DOWN:
                        break;
                    case SDLK_RIGHT:
                        break;
                    case SDLK_LEFT:
                        break;
                }
            }

            else if (event.type == SDL_KEYUP) {
                // Se soltó una tecla
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        mover = false;
                        break;
                    case SDLK_DOWN:
                        break;
                    case SDLK_RIGHT:
                        break;
                    case SDLK_LEFT:
                        break;
                }
            }
            // END código del alumno
            continue;
        }

        // BEGIN código del alumno


        imagen_t *cuadro = imagen_generar(320, 224, 0x00f);

        if(mover)
            x += 1;
        if(x > 320)
            x = -10;

        /*generacion de fondo*/

        imagen_t *fondo1 = generar_mosaico(teselas, paleta_3, FONDO1_FILAS, FONDO1_COLUMNAS, fondo1_mosaico, fondo1_paleta);
        imagen_t *fondo2 = generar_mosaico(teselas, paleta_3, FONDO2_FILAS, FONDO2_COLUMNAS, fondo2_mosaico, fondo2_paleta);

        imagen_pegar(cuadro, fondo2, /*-20*/ -x*2, 64);
        imagen_pegar(cuadro, fondo1, /*-1126*/-x, 112);

        imagen_destruir(fondo1);
        imagen_destruir(fondo2);

        imagen_t *pasto = generar_pasto();

        imagen_pegar(cuadro, pasto, 0, 128);
        imagen_destruir(pasto);

        imagen_t *cuadrado = imagen_generar(10, 10, 0x0f0);
        imagen_pegar(cuadro, cuadrado, x, (224 - 10) / 2);
        imagen_destruir(cuadrado);

        // Procedemos a dibujar a pantalla completa:
        imagen_t *cuadro_escalado = imagen_escalar(cuadro, VENTANA_ANCHO, VENTANA_ALTO);
        // Hay que implementar esta función que dibuja de forma eficiente:
        imagen_a_textura(cuadro_escalado, canvas);
        // Como todavía no la tenemos lo hacemos de forma ineficiente con primitivas:
        /*
        for(size_t f = 0; f < imagen_get_alto(cuadro_escalado); f++)
            for(size_t c = 0; c < imagen_get_ancho(cuadro_escalado); c++)
                canvas[f * imagen_get_ancho(cuadro_escalado) + c] = imagen_get_pixel(cuadro_escalado, c, f);
        */
        // Implementar imagen_a_textura() cuanto antes!

        imagen_destruir(cuadro_escalado);
        imagen_destruir(cuadro);

        // END código del alumno

        SDL_UpdateTexture(texture, NULL, canvas, VENTANA_ANCHO * sizeof(uint16_t));
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
        ticks = SDL_GetTicks() - ticks;
        if(dormir) {
            SDL_Delay(dormir);
            dormir = 0;
        }
        else if(ticks < 1000 / JUEGO_FPS)
            SDL_Delay(1000 / JUEGO_FPS - ticks);
        else
            printf("Perdiendo cuadros\n");
        ticks = SDL_GetTicks();
    }

    // BEGIN código del alumno
    // No tengo nada que destruir.
    // END código del alumno

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}

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

/*
    funcion: generar_pasto
    Devuelve una imagen del pasto de la parte inferior de la imagen
*/

imagen_t *generar_pasto(){

    pixel_t colores_pasto[10] = {0x089, 0x099, 0x099, 0x0a9, 0x0a9, 0x0a9, 0x0b9, 0x0b9, 0x0c9, 0x0c9};

    imagen_t *pasto = imagen_generar(1, 96, pixel12_crear(0, 13, 9));

    for(size_t i = 0; i < 10; i++)
        imagen_set_pixel(pasto, 0, i, colores_pasto[i]);

    imagen_t *pasto_estirado = imagen_escalar(pasto, 320, 96);

    imagen_destruir(pasto);

    return pasto_estirado;
}

