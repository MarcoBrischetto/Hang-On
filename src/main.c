#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdlib.h>

#include "config.h"
#include "imagen.h"
#include "ruta.h"
#include "paleta.h"
#include "fondo.h"
#include "pixel.h"
#include "figura.h"
#include "teselas.h"
#include "moto.h"
#include "ecuaciones.h"
#include "textos.h"
#include "fisica.h"
#include "semaforo.h"


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
    double tiempo_restante = 75;
    double tiempo_total = 0;
    double temporizador = 0;
    double posicion_moto_anterior;
    mef_semaforo_t estado_semaforo = APAGADO;

    double fondo1_x = FONDO_X_INICIAL;
    double fondo2_x = FONDO_X_INICIAL;

    double ul[POSICIONES_VECTOR];
    double uc[POSICIONES_VECTOR];
    double ur[POSICIONES_VECTOR];

    uint16_t rom[CANTIDAD_VALORES_ROMS] = {0};
    if(cargar_figuras_rom(rom) == false) return 1;

    moto_t *moto = moto_crear();
    if(moto == NULL) return 1;

    imagen_t *teselas[CANTIDAD_TESELAS];

    if(!cargar_teselas(teselas)){
        moto_destruir(moto);
        return 1;
    }

    imagen_t *img_ruta = ruta_cargar_rom();

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
                        moto_set_acelerar(moto, true);
                        break;
                    case SDLK_DOWN:
                        moto_set_freno(moto, true);
                        break;
                    case SDLK_RIGHT:
                        moto_set_der(moto, true);
                        break;
                    case SDLK_LEFT:
                        moto_set_izq(moto, true);
                        break;
                }
            }

            else if (event.type == SDL_KEYUP) {
                // Se soltó una tecla
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        moto_set_acelerar(moto, false);
                        break;
                    case SDLK_DOWN:
                        moto_set_freno(moto, false);
                        break;
                    case SDLK_RIGHT:
                        moto_set_der(moto, false);
                        break;
                    case SDLK_LEFT:
                        moto_set_izq(moto, false);
                        break;
                }
            }
            // END código del alumno
            continue;
        }

        // BEGIN código del alumno

        if(moto_get_ganar(moto) || moto_get_perder(moto)){
            continue;
        }

        /*fisicas*/

        posicion_moto_anterior = moto_get_x(moto);

        desplazamiento_lateral(ul, moto_get_y(moto));
        desplazamiento_curva(uc, ruta, (size_t)moto_get_x(moto));
        desplazamiento_total(uc, ul, ur);

        if(estado_semaforo >= VERDE) tiempo_restante -= 1.0/JUEGO_FPS;

        tiempo_total += 1.0/JUEGO_FPS;

        moto_computar_fisicas(moto, 1.0/JUEGO_FPS, tiempo_restante, ruta, ur);

        /*Choques*/

        if(tiempo_total - temporizador > TIEMPO_CHOQUE && moto_get_choque(moto)){
            temporizador = tiempo_total;
            moto_set_choque(moto, false);
        }

        if(!moto_get_choque(moto)) temporizador = tiempo_total;

        /*generacion de fondo*/

        if(fondo1_x > FONDO_X_INICIAL){
            fondo1_x = FONDO_LIMITE;
            fondo2_x = FONDO_LIMITE;
        }

        if(fondo1_x < FONDO_LIMITE){
            fondo1_x = FONDO_X_INICIAL;
            fondo2_x = FONDO_X_INICIAL;
        }


        fondo2_x -= desplazamiento_fondo(moto_get_x(moto), posicion_moto_anterior, ruta);
        fondo1_x -= RELACION_FONDOS*desplazamiento_fondo(moto_get_x(moto), posicion_moto_anterior, ruta);

        imagen_t *cuadro = imagen_generar(320, 224, 0x00f);

        imagen_t *fondo1 = generar_mosaico(teselas, paleta_3, FONDO1_FILAS, FONDO1_COLUMNAS, fondo1_mosaico, fondo1_paleta);
        imagen_t *fondo2 = generar_mosaico(teselas, paleta_3, FONDO2_FILAS, FONDO2_COLUMNAS, fondo2_mosaico, fondo2_paleta);

        imagen_pegar(cuadro, fondo2, fondo1_x, FONDO1_Y, false);
        imagen_pegar(cuadro, fondo1, fondo2_x, FONDO2_Y, false);

        imagen_destruir(fondo1);
        imagen_destruir(fondo2);

        imagen_t *pasto = generar_pasto();

        imagen_pegar(cuadro, pasto, 0, 128, false);
        imagen_destruir(pasto);

        /*ruta*/

        ruta_dibujar(cuadro, img_ruta, ur, moto_get_x(moto), ruta);
        ruta_dibujar_figuras(cuadro, ruta, ur, moto_get_x(moto), rom, paleta_4);

        /*moto*/

        imagen_t *moto1 = moto_get_figura(moto, rom);
        imagen_pegar_con_paleta(cuadro, moto1, moto_dibujado_x(moto), moto_dibujado_y(moto), paleta_4[moto_get_paleta(moto)], false);
        imagen_destruir(moto1);

        /*Semaforo*/

        estado_semaforo =  mef_semaforo(estado_semaforo, rom, cuadro, tiempo_total, moto_get_x(moto), ur, paleta_4);

        if(estado_semaforo == VERDE) moto_set_largada(moto, false);

        /*Textos*/

        generar_textos_estaticos(cuadro, teselas);
        generar_textos_variables(cuadro, teselas, moto_get_velocidad(moto), moto_get_puntaje(moto), tiempo_restante);

        if(moto_get_perder(moto)){
            imagen_t *game_over = generar_mosaico(teselas, paleta_3, GAME_OVER_FILAS, GAME_OVER_COLUMNAS, game_over_mosaico, game_over_paleta);
            imagen_pegar(cuadro, game_over, 96, 56, false);
            imagen_destruir(game_over);
        }

        if(moto_get_ganar(moto)){
            imagen_t *goal = obtener_figura(rom, tabla_figuras[GOAL].pos, tabla_figuras[GOAL].ancho, tabla_figuras[GOAL].alto);
            imagen_pegar_con_paleta(cuadro, goal, 96, 56, paleta_4[30], false);
            imagen_destruir(goal);
        }


        // Procedemos a dibujar a pantalla completa:
        imagen_t *cuadro_escalado = imagen_escalar(cuadro, VENTANA_ANCHO, VENTANA_ALTO);
        imagen_a_textura(cuadro_escalado, canvas);

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

    // BEGIN código del alumnos
    moto_destruir(moto);
    imagen_destruir(img_ruta);
    liberar_teselas(teselas);
    // END código del alumno

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}



