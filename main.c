#include <SDL2/SDL.h>
#include <stdbool.h>

#include "config.h"
#include "imagen.h"
#include "ruta.h"
#include "paleta.h"
#include "fondo.h"
#include "pixel.h"
#include "figura.h"
#include "teselas.h"
#include "moto.h"

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
    int intensidad = 0;


    uint16_t rom[CANTIDAD_VALORES_ROMS];
    if(cargar_figuras_rom(rom) == false) return 1;

    //imagen_t *moto1 = obtener_figura(rom, 532, 36, 73);
    moto_t *moto = moto_crear();
    if(moto == NULL) return 1;

    /*
    for(size_t i = 0; i < CANTIDAD_VALORES_ROMS; i++)
        printf("%x\n ", rom[i]);

    return 0;
*/
    imagen_t *teselas[CANTIDAD_TESELAS];

    cargar_teselas(teselas);

    //imagen_t *ruta = ruta_cargar_rom();

    //imagen_guardar_ppm(ruta, "prueba.txt", pixel3_a_rgb);

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
                        moto_set_der(moto, true);
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
                        moto_set_der(moto, false);
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


        if(moto_get_der(moto))intensidad++;

        if(!moto_get_der(moto))intensidad--;

        if(intensidad > 1) intensidad = 1;

        if(intensidad < 0) intensidad = 0;

        moto_set_intensidad(moto, intensidad);

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

        //imagen_pegar_con_paleta(cuadro, ruta, -300, 0, colores_ruta[0]);

        /*moto*/

        //imagen_t *moto1 = obtener_figura(rom, 17215, 60, 54);
        imagen_t *moto1 = moto_get_figura(moto, rom);
        imagen_pegar_con_paleta(cuadro, moto1, 100, 0, paleta_4[1]);
        imagen_destruir(moto1);

        //imagen_pegar_con_paleta(cuadro, espejado, 50, 100, paleta_4[2]);
        //imagen_pegar(cuadro, ruta, -300, 0);


        //imagen_t *cuadrado = imagen_generar(10, 10, 0x0f0);
        //imagen_pegar(cuadro, cuadrado, x, (224 - 10) / 2);
        //imagen_destruir(cuadrado);

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
    moto_destruir(moto);
    //imagen_destruir(espejado);
    //imagen_destruir(ruta);
    liberar_teselas(teselas);
    // END código del alumno

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
