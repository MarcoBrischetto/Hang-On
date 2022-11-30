#include "semaforo.h"
#include "ecuaciones.h"

const semaforo_t tabla_semaforo_apagado[] = {

    {SEMAFORO, 41, 215, 0},
    {SEMAFORO, 41, -215, 0},
    {VIGA, 45, 145, 0},
    {VIGA, 45, -145, 0},
    {BANNER, 45, 0, 0}

};

const semaforo_t tabla_semaforo_amarillo[] = {

    {SEMAFORO, 42, 215, 0},
    {SEMAFORO, 42, -215, 0},
    {VIGA, 45, 145, 0},
    {VIGA, 45, -145, 0},
    {BANNER, 45, 0, 0}

};

const semaforo_t tabla_semaforo_rojo[] = {

    {SEMAFORO, 43, 215, 0},
    {SEMAFORO, 43, -215, 0},
    {VIGA, 45, 145, 0},
    {VIGA, 45, -145, 0},
    {BANNER, 45, 0, 0},
};

const semaforo_t tabla_semaforo_verde[] = {
    {SEMAFORO, 44, 215, 0},
    {SEMAFORO, 44, -215, 0},
    {VIGA, 45, 145, 0},
    {VIGA, 45, -145, 0},
    {BANNER, 45, 0, 0}
};

const semaforo_t tabla_semaforo_llegada[] = {
    {SEMAFORO, 41, 215, 0},
    {SEMAFORO, 41, -215, 0},
    {VIGA, 45, 145, 0},
    {VIGA, 45, -145, 0},
    {BANNER, 47, 0, 0}
};


mef_semaforo_t mef_semaforo(mef_semaforo_t estado, uint16_t *rom, imagen_t *cuadro, double tiempo, double x, double *ur, const pixel_t paleta[][16]){

    switch(estado){

        case APAGADO:

            dibujar_semaforo(rom, x, 6, tiempo, cuadro, paleta, ur, tabla_semaforo_apagado);

            if(tiempo > 1) estado = AMARILLO;

            break;

        case AMARILLO:

            dibujar_semaforo(rom, x, 6, tiempo, cuadro, paleta, ur, tabla_semaforo_amarillo);

            if(tiempo > 2) estado = ROJO;

            break;

        case ROJO:

            dibujar_semaforo(rom, x, 6, tiempo, cuadro, paleta, ur, tabla_semaforo_rojo);

            if(tiempo > 3) estado = VERDE;

            break;

        case VERDE:

            dibujar_semaforo(rom, x, 6, tiempo, cuadro, paleta, ur, tabla_semaforo_verde);

            if(x >= 6) estado = SIN_SEMAFORO;

            break;

        case SIN_SEMAFORO:

            if(x > 4200 - CAMPO_VISION) estado = LLEGADA;

            break;

        case LLEGADA:

            dibujar_semaforo(rom, x, 4200, tiempo, cuadro, paleta, ur, tabla_semaforo_llegada);

            break;

        default:

            break;
    }

    return estado;
}


void dibujar_semaforo(uint16_t *rom, double x, double xs,double tiempo, imagen_t *cuadro, const pixel_t paleta[][16], double *ur, const semaforo_t tabla_semaforo[]){

        int d = xs - x;

        imagen_t *imagen;

        for(size_t i = 0; i < 5; i++){

            enum figura figura = tabla_semaforo[i].figura;

            size_t alto = tabla_figuras[figura].alto;

            imagen_t *imagen_rom = obtener_figura(rom, tabla_figuras[figura].pos, tabla_figuras[figura].ancho, alto);

            if(figura == VIGA || figura == BANNER){
                alto = 249;
                imagen = imagen_generar(tabla_figuras[figura].ancho, alto, 0);
                imagen_pegar(imagen, imagen_rom, 0, 0, false);
                imagen_destruir(imagen_rom);
            }
            else imagen = imagen_rom;


            double alto_escalado = escalado_h(v(d), alto);
            double ancho_escalado = escalado_ancho(v(d), tabla_figuras[figura].ancho);

            imagen_t *img_fig_escalada = imagen_escalar(imagen, ancho_escalado, alto_escalado);

            imagen_destruir(imagen);

            size_t idx_paleta = tabla_semaforo[i].paleta;
            int yx = tabla_semaforo[i].y;
            bool reflejar = tabla_semaforo[i].reflejar;

            double pos_u = u(yx, v(d), ur) + U - ancho_escalado/2;
            double pos_v = V - v(d) - alto_escalado;

            imagen_pegar_con_paleta(cuadro, img_fig_escalada, pos_u, pos_v, paleta[idx_paleta], reflejar);

            imagen_destruir(img_fig_escalada);
        }

}


/*
        imagen_t *viga_rom = obtener_figura(rom, tabla_figuras[VIGA].pos, tabla_figuras[VIGA].ancho, tabla_figuras[VIGA].alto);
        imagen_t *viga = imagen_generar(198, 249, 0);
        imagen_pegar(viga, viga_rom, 0, 0, false);
        imagen_pegar_con_paleta(cuadro, viga, 0, 0, paleta_4[45], false);
        imagen_destruir(viga_rom);

        imagen_t *banner_rom = obtener_figura(rom, tabla_figuras[BANNER].pos, tabla_figuras[BANNER].ancho, tabla_figuras[BANNER].alto);
        imagen_t *banner = imagen_generar(244, 249, 0);
        imagen_pegar(banner, banner_rom, 0, 0, false);
        imagen_pegar_con_paleta(cuadro, banner, 200, 0, paleta_4[45], false);
        imagen_destruir(banner_rom);

        imagen_t *semaforo = obtener_figura(rom, tabla_figuras[SEMAFORO].pos, tabla_figuras[SEMAFORO].ancho, tabla_figuras[SEMAFORO].alto);

        imagen_pegar_con_paleta(cuadro, semaforo, 200, 100, paleta_4[41], false);

        imagen_destruir(semaforo);

        imagen_t *banner = obtener_figura(rom, tabla_figuras[BANNER].pos, tabla_figuras[BANNER].ancho, tabla_figuras[BANNER].alto);

        imagen_pegar_con_paleta(cuadro, viga, 0, 0);


        imagen_pegar_con_paleta(cuadro, semaforo, 0, 0);
        imagen_pegar_con_paleta(cuadro, banner, 0, 0);*/
